/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vis.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggerardy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/20 01:27:29 by ggerardy          #+#    #+#             */
/*   Updated: 2019/04/20 01:27:29 by ggerardy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "len_in.h"

#define GRAY 0x002e2e2e
#define GRAD_START (t_hsv){0, 90, 60}
#define GRAD_END (t_hsv){180, 90, 60}
#define GRAD_DIR -1



void 	ft_print_map(void *p)
{
	t_mlx	*mlx;
	t_data	*dt;
	t_vis_dims *ds;
	int 	i;

	mlx = p;
	i = -1;
	dt = mlx->add_data;
	ds = dt->dims;

	t_point size;

	size = (t_point){ds->side, ds->side * dt->ant_count};
	int x_pad = DEFAULT_H_PAD + ds->h_pad;
	int y_pad = DEFAULT_V_PAD + ds->gap;

	/*int		width = 1;
	int 	height = 1;
	int 	gap = 1;
	int 	pad = 50;
	int 	len = mlx->x - 2 * pad;*/

	int j;
	while (++i < dt->real_nodes_count)
	{
		int x_pos = (i % ds->line_len) * ds->side;
		int y_pos = (i / ds->line_len) * (dt->ant_count * ds->side + ds->gap);
		ft_mlx_rectput(mlx, size,
				(t_point){x_pad + x_pos, y_pad + y_pos},
				ft_hsv_gradient(GRAD_START, GRAD_END,
			(double[3]){0, dt->sorted_nodes[i].dst, dt->max_dst}, GRAD_DIR));
		if (ds->side >= 4 && (j = -1))
			while (++j < dt->ant_count)
			ft_mlx_frameput(mlx, (t_point){ds->side, ds->side},
					(t_point){x_pad + x_pos, y_pad + y_pos + j * ds->side}, 0x00191919);
	}
}

int 	ft_mlx_expose(void *p)
{
	t_mlx *mlx;

	mlx = p;
	ft_mlx_rectput(mlx, (t_point){mlx->x, mlx->y}, (t_point){0, 0}, GRAY);

	ft_print_map(p);
	ft_mlx_put_img(mlx);
	return (0);
}
