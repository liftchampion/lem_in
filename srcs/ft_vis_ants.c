/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vis_ants.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggerardy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 10:53:52 by ggerardy          #+#    #+#             */
/*   Updated: 2019/04/24 10:53:52 by ggerardy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "len_in.h"

#ifndef NO_VISUALIZATION

void				ft_fill_ants_poses(t_data *dt, const int *waves,
					int wave_count)
{
	int	i;
	int j;
	int start;

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

int					ft_vis_init_ants(t_data *dt)
{
	int			wave_count;
	t_vector	**paths;

	ft_bzero(dt->ants, sizeof(t_ant) * dt->ant_count);
	ft_bzero(dt->gone_ants, dt->ant_count);
	if (dt->special_case > 0)
		return (1);
	paths = (t_vector**)((t_vector*)dt->flows->data[dt->best_flow])->data;
	ft_send_lems_last_way(dt, dt->best_flow,
		((t_vector*)dt->flows->data[dt->best_flow])->len - 1, dt->ant_count);
	free(dt->wave_sizes);
	wave_count = paths[0]->offset + paths[0]->len;
	if (!ft_fill_ants(dt))
		return (0);
	ft_fill_ants_poses(dt, dt->wave_sizes, wave_count);
	return (1);
}

static inline int	ft_get_ant_node(t_data *dt, int i)
{
	t_vector	*path;
	int			node;

	if (dt->special_case == 1)
		return (0);
	if (dt->special_case == 2)
		return (!CURR_POS ? 0 : dt->name_to_pos[dt->end - 1]);
	path = ((t_vector*)dt->flows->data[dt->best_flow])->data[CURR_PATH];
	if (CURR_POS <= 0)
		node = 0;
	else if (CURR_POS > (int)path->len)
		node = dt->name_to_pos[dt->end - 1];
	else
		node = dt->name_to_pos[(int)path->data[path->len - CURR_POS]];
	return (node);
}

void				ft_draw_ants(t_data *dt)
{
	int i;
	int node;
	int x_pos;
	int y_pos;

	i = -1;
	while (++i < dt->ant_count)
	{
		node = ft_get_ant_node(dt, i);
		x_pos = DEFAULT_H_PAD + dt->dims->h_pad +
				(node % dt->dims->line_len) * dt->dims->side;
		y_pos = DEFAULT_V_PAD + dt->dims->gap +
				(node / dt->dims->line_len) *
						(dt->ant_count * dt->dims->side + dt->dims->gap) +
				i * dt->dims->side;
		ft_mlx_rectput(dt->mlx, (t_point){dt->dims->side, dt->dims->side},
				(t_point){x_pos, y_pos}, ANT_COLOR);
		if (dt->dims->side >= 10)
			ft_mlx_frameput(dt->mlx, (t_point){dt->dims->side, dt->dims->side},
					(t_point){x_pos, y_pos}, BORDERS_COLOR);
	}
}

#endif
