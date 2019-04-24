/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vis_drawers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggerardy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 10:49:52 by ggerardy          #+#    #+#             */
/*   Updated: 2019/04/24 10:49:52 by ggerardy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "len_in.h"

#ifndef NO_VISUALIZATION

void				ft_print_map_one_unit(t_data *dt, int i, int x_pad,
					int y_pad)
{
	int			x_pos;
	int			y_pos;
	t_vis_dims	*ds;
	int			j;
	t_point		size;

	ds = dt->dims;
	size = (t_point){ds->side, ds->side * dt->ant_count};
	x_pos = (i % ds->line_len) * ds->side;
	y_pos = (i / ds->line_len) * (dt->ant_count * ds->side + ds->gap);
	ft_mlx_rectput(dt->mlx, size,
			(t_point){x_pad + x_pos, y_pad + y_pos}, ft_get_color(dt, i));
	if (ds->side >= 10 && (j = -1))
		while (++j < dt->ant_count)
			ft_mlx_frameput(dt->mlx, (t_point){ds->side, ds->side},
					(t_point){x_pad + x_pos, y_pad + y_pos + j * ds->side},
					BORDERS_COLOR);
}

void				ft_print_map(void *p)
{
	t_mlx		*mlx;
	t_data		*dt;
	t_vis_dims	*ds;
	int			i;

	mlx = p;
	i = -1;
	dt = mlx->add_data;
	ds = dt->dims;
	while (++i < dt->real_nodes_count)
		ft_print_map_one_unit(dt, i,
				DEFAULT_H_PAD + ds->h_pad, DEFAULT_V_PAD + ds->gap);
}

void				ft_print_texts_one_unit(t_data *dt, int i, int x_pad,
					int y_pad)
{
	char	name[128];
	int		x_pos;
	int		y_pos;
	int		j;
	char	*ant;

	ft_strlcpy(name,
			((t_node*)dt->nodes->data[dt->sorted_nodes[i].name])->name, 128);
	x_pos = (i % dt->dims->line_len) * dt->dims->side;
	y_pos = (i / dt->dims->line_len) * (dt->ant_count * dt->dims->side +
			dt->dims->gap);
	if (dt->dims->use_text_nodes)
		mlx_string_put(dt->mlx->mlx_ptr, dt->mlx->win_ptr,
				x_pad + x_pos + (dt->dims->side - ft_strlen(name) * 10) / 2,
				y_pad + y_pos - TEXT_H, TEXT_COLOR, name);
	if (!i % dt->dims->line_len && dt->dims->use_text_ants && (j = -1))
		while (++j < dt->ant_count)
		{
			ant = dt->prs->ant_names ? dt->ant_names->data[j] :
					ft_itoa_buf(j, name);
			mlx_string_put(dt->mlx->mlx_ptr, dt->mlx->win_ptr, x_pad + x_pos
					- dt->dims->longest_ant_name * 11, y_pad + y_pos +
				j * dt->dims->side + dt->dims->side / 2 - 11, TEXT_COLOR, ant);
		}
}

void				ft_print_texts(void *p)
{
	t_mlx		*mlx;
	t_data		*dt;
	t_vis_dims	*ds;
	int			i;
	char		*turn_str;

	mlx = p;
	i = -1;
	dt = mlx->add_data;
	ds = dt->dims;
	ft_sprintf(&turn_str, "Turn %d/%d", dt->curr_turn,
			dt->req_turns ? dt->req_turns : dt->turns);
	if (!turn_str)
		ft_destroy_mlx(mlx, 0);
	mlx_string_put(mlx->mlx_ptr, mlx->win_ptr,
			mlx->x - 10 - ft_strlen(turn_str) * 11,
			mlx->y - 10 - 18, TURNS_COLOR, turn_str);
	while (++i < dt->real_nodes_count)
		ft_print_texts_one_unit(dt, i,
				DEFAULT_H_PAD + ds->h_pad, DEFAULT_V_PAD + ds->gap);
}

#endif
