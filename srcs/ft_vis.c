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
#define BORDERS_COLOR 0x00191919
#define GRAD_START (t_hsv){0, 90, 60}
#define GRAD_END (t_hsv){180, 90, 60}
#define GRAD_DIR -1

#ifndef NO_VISUALIZATION

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
	//int x_pad = DEFAULT_H_PAD + ds->h_pad + ds->use_text_ants * ds->longest_ant_name * 15;
	int x_pad = DEFAULT_H_PAD + ds->h_pad;
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
					(t_point){x_pad + x_pos, y_pad + y_pos + j * ds->side}, BORDERS_COLOR);
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

void 	ft_fill_ants_poses(t_data *dt, const int *waves, int wave_count)
{
	int			i;
	int 		j;
	int 		start;

	i = 0;
	start = waves[0];
	while (++i < wave_count)
	{
		j = start - 1;
		while (++j < dt->ant_count)
		{
			--dt->ants[j].pos;
		}
		start += waves[i];
	}
}

void 	ft_turn(t_data *dt, int turn)
{
	int i;

	i = -1;
	while (++i < dt->ant_count)
	{
		dt->ants[i].pos += turn;
	}
}

int 	ft_vis_init_ants(t_data *dt)
{
	int			wave_count;
	t_vector	**paths;

	paths = (t_vector**)((t_vector*)dt->flows->data[dt->best_flow])->data;
	ft_send_lems_last_way(dt, dt->best_flow,
		((t_vector*)dt->flows->data[dt->best_flow])->len - 1, dt->ant_count);
	free(dt->wave_sizes);
	ft_bzero(dt->ants, sizeof(t_ant) * dt->ant_count);
	ft_bzero(dt->gone_ants, dt->ant_count);
	wave_count = paths[0]->offset + paths[0]->len;
	if (!ft_fill_ants(dt))
		return (0);
	ft_fill_ants_poses(dt, dt->wave_sizes, wave_count);
	ft_turn(dt, 1);
	ft_turn(dt, 1);
	ft_turn(dt, 1);
	ft_turn(dt, 1);
	ft_turn(dt, 1);
	ft_turn(dt, 1);
	ft_turn(dt, 1);
	ft_turn(dt, 1);
	ft_turn(dt, 1);
	ft_turn(dt, 1);
	return (1);
}

void 	ft_draw_ants(t_data *dt)
{
	int			i;
	int			node;
	t_vector	*path;
	int 		x_pos;
	int 		y_pos;

	i = -1;
	while (++i < dt->ant_count)
	{
		path = ((t_vector*)dt->flows->data[dt->best_flow])->data[CURR_PATH];
		ft_printf("%d/%d\n", CURR_POS, path->len);
		if (CURR_POS <= 0)
			node = 0;
		else if (CURR_POS > (int)path->len)
			node = dt->name_to_pos[dt->end - 1];
		else
			node = dt->name_to_pos[(int)path->data[path->len - CURR_POS]];
		x_pos = DEFAULT_H_PAD + dt->dims->h_pad +
				(node % dt->dims->line_len) * dt->dims->side;
		y_pos = DEFAULT_V_PAD + dt->dims->gap +
				(node / dt->dims->line_len) *
				(dt->ant_count * dt->dims->side + dt->dims->gap) +
				i * dt->dims->side;
		ft_mlx_rectput(dt->mlx, (t_point){dt->dims->side, dt->dims->side},
				(t_point){x_pos, y_pos}, 0x00FFFFFF);
		if (dt->dims->side >= 10)
			ft_mlx_frameput(dt->mlx, (t_point){dt->dims->side, dt->dims->side},
					(t_point){x_pos, y_pos}, BORDERS_COLOR);

	}
}

int 	ft_mlx_expose(void *p)
{
	t_mlx *mlx;

	mlx = p;
	if (!ft_vis_init_ants(mlx->add_data))
		return (0); // todo do it before ! todo free exit trah babah

	ft_mlx_rectput(mlx, (t_point){mlx->x, mlx->y}, (t_point){0, 0}, GRAY);

	ft_print_map(p);
	ft_draw_ants(mlx->add_data);
	ft_mlx_put_img(mlx);
	ft_print_texts(p);
	//mlx_string_put(mlx->mlx_ptr, mlx->win_ptr, 10, 10, 0x000000ff, "WAA");
	return (0);
}

int		ft_visualize(t_data *dt)
{
	dt->screen_h = 1080;
	dt->screen_w = 2400;
	if (ft_get_dims(dt) <= 0)
		return (ft_free_data(dt, 0) * ft_printf("Dimensions Error\n"));
	if (!(dt->mlx = ft_mlx_init(dt->screen_w, dt->screen_h, "Super Muravii",
			(t_mlx_init){dt, dt, ft_free_for_mlx, 0, 0, ft_mlx_expose, 0})))
		return (ft_printf("MLX Error\n") * 0);
	mlx_loop(dt->mlx->mlx_ptr);
	return (1);
}

#else

int		ft_visualize(t_data *dt)
{
	dt = 0;
	ft_printf("Visualisation is {Red}disabled{eof}!\n");
	return (1);
}

#endif
