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
#define UNREACHING_NODES_COLOR 0x00101010
#define TEXT_COLOR 0x00E0E0E0
#define GRAD_START (t_hsv){0, 90, 60}
#define GRAD_END (t_hsv){180, 90, 60}
#define GRAD_DIR -1

unsigned int	ft_get_color(t_data *dt, int i)
{
	unsigned int res;

	if (dt->sorted_nodes[i].dst != INF)
		res = ft_hsv_gradient(GRAD_START, GRAD_END,
			(double[3]){0, dt->sorted_nodes[i].dst, dt->max_dst}, GRAD_DIR);
	else
		res = UNREACHING_NODES_COLOR;
	return (res);
}

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
	int x_pad = DEFAULT_H_PAD + ds->h_pad + ds->use_text_ants * ds->longest_ant_name * 15;
	int y_pad = DEFAULT_V_PAD + ds->gap;

	int j;
	while (++i < dt->real_nodes_count)
	{
		int x_pos = (i % ds->line_len) * ds->side;
		int y_pos = (i / ds->line_len) * (dt->ant_count * ds->side + ds->gap);
		ft_mlx_rectput(mlx, size,
				(t_point){x_pad + x_pos, y_pad + y_pos}, ft_get_color(dt, i));
		if (ds->side >= 10 && (j = -1))
			while (++j < dt->ant_count)
			ft_mlx_frameput(mlx, (t_point){ds->side, ds->side},
					(t_point){x_pad + x_pos, y_pad + y_pos + j * ds->side}, 0x00191919);
	}
}

void 	ft_print_texts(void *p)
{
	t_mlx	*mlx;
	t_data	*dt;
	t_vis_dims *ds;
	int 	i;
	int 	j;

	mlx = p;
	i = -1;
	dt = mlx->add_data;
	ds = dt->dims;

	int x_pad = DEFAULT_H_PAD + ds->h_pad;
	int y_pad = DEFAULT_V_PAD + ds->gap;

	char *name;

	while (++i < dt->real_nodes_count)
	{
		name = ((t_node*)dt->nodes->data[dt->sorted_nodes[i].name])->name;
		int x_pos = (i % ds->line_len) * ds->side;
		int y_pos = (i / ds->line_len) * (dt->ant_count * ds->side + ds->gap);
		if (ds->use_text_nodes)
			mlx_string_put(mlx->mlx_ptr, mlx->win_ptr,
					x_pad + x_pos + (ds->side - ft_strlen(name) * 10) / 2, y_pad + y_pos - 18, TEXT_COLOR, name);
		if (!i % ds->line_len && ds->longest_ant_name * 15 < ds->h_pad && (j = -1))
		{
			while (++j < dt->ant_count)
			{
				char *ant;
				ant = dt->prs->ant_names ? dt->ant_names->data[j] : ft_itoa(j);
				mlx_string_put(mlx->mlx_ptr, mlx->win_ptr,
						x_pad + x_pos - ds->longest_ant_name * 11,
						y_pad + y_pos + j * ds->side + ds->side / 2 - 11,
						TEXT_COLOR, ant);
			}
		}
	}
}

int 	ft_mlx_expose(void *p)
{
	t_mlx *mlx;

	mlx = p;
	ft_mlx_rectput(mlx, (t_point){mlx->x, mlx->y}, (t_point){0, 0}, GRAY);

	ft_print_map(p);
	ft_mlx_put_img(mlx);
	ft_print_texts(p);
	//mlx_string_put(mlx->mlx_ptr, mlx->win_ptr, 10, 10, 0x000000ff, "WAA");
	return (0);
}
/*
int 	ft_visualize(t_data *dt)
{

}*/
