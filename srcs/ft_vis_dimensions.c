/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vis_dimensions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggerardy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 10:56:52 by ggerardy          #+#    #+#             */
/*   Updated: 2019/04/24 10:56:52 by ggerardy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "len_in.h"
#include "math.h"

void				ft_set_dims(t_data *dt, t_vis_dims *ds)
{
	ds->line_len = ds->width / ds->side;
	ds->lines_count =
			(int)((1. * dt->real_nodes_count) / ds->line_len + 0.999999);
	if (ds->lines_count != 1)
		ds->gap = (ds->height - ds->lines_count * dt->ant_count * ds->side) /
				(ds->lines_count - 1);
	else
		ds->gap = 0;
	ds->h = dt->ant_count * ds->side * ds->lines_count +
			ds->gap * (ds->lines_count - 1);
}

int					ft_get_dims_start(t_data *dt)
{
	t_vis_dims *ds;

	if (!dt->real_nodes_count)
	{
		dijkstra(dt);
		ft_copy_nodes(dt);
	}
	if (!(dt->dims = ft_memalloc(sizeof(t_vis_dims))))
		return (0);
	ds = dt->dims;
	ds->width = dt->screen_w - 2 * DEFAULT_H_PAD;
	ds->height = dt->screen_h - 2 * DEFAULT_V_PAD;
	ds->h = INF;
	ds->side = (int)sqrt((1. * ds->width * ds->height) /
			(dt->ant_count * dt->real_nodes_count));
	if (!ds->side)
		return (-1);
	ft_set_dims(dt, ds);
	return (1);
}

void				ft_get_dims_end(t_data *dt)
{
	int			free_space[2];
	t_vis_dims	*ds;

	if (dt->dims->side)
		ft_check_text_nodes(dt);
	if (dt->dims->side)
		ft_check_text_ants(dt);
	ds = dt->dims;
	free_space[0] = ds->width - (dt->real_nodes_count < ds->line_len ?
			dt->real_nodes_count : ds->line_len) * ds->side;
	free_space[1] = ds->height - dt->ant_count * ds->side * ds->lines_count -
			TEXT_H * ds->use_text_nodes * ds->lines_count;
	free_space[1] = free_space[1] < 0 ? 0 : free_space[1];
	if (free_space[1] / (ds->lines_count + 1))
		ds->gap = free_space[1] / (ds->lines_count + 1);
	ds->gap += ds->use_text_nodes * TEXT_H;
	ds->h_pad = free_space[0] / 2;
}

int					ft_get_dims(t_data *dt)
{
	int			start_ret;
	t_vis_dims	*ds;

	if ((start_ret = ft_get_dims_start(dt)) <= 0)
		return (start_ret);
	ds = dt->dims;
	while (ds->side)
	{
		if (ds->h <= ds->height && (ds->gap > 0 || ds->lines_count == 1))
			break ;
		if (--ds->side)
			ft_set_dims(dt, ds);
	}
	ft_get_dims_end(dt);
	return (dt->dims->side ? 1 : -1);
}
