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
	int 	i;

	mlx = p;
	i = -1;
	dt = mlx->add_data;

	int		width = 1;
	int 	height = 1;
	int 	gap = 1;
	int 	pad = 50;
	int 	len = mlx->x - 2 * pad;

	while (++i < dt->real_nodes_count)
	{
		ft_mlx_rectput(mlx,
				(t_point){width, height * dt->ant_count},
				(t_point){pad + width * (i % len),
			  	  	  pad + (height * dt->ant_count + gap) * (i / len)},
				ft_hsv_gradient(GRAD_START, GRAD_END,
			(double[3]){0, dt->sorted_nodes[i].dst, dt->max_dst}, GRAD_DIR));
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
