/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vis_save_nodes.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggerardy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/20 06:05:47 by ggerardy          #+#    #+#             */
/*   Updated: 2019/04/20 06:05:47 by ggerardy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "len_in.h"
#include "math.h"

void 	ft_set_dims(t_data *dt)
{
	t_vis_dims	*ds;

	ds = dt->dims;
	ds->lines_count =
			(int)((1. * ds->side * dt->real_nodes_count) / ds->width  + 0.999999);
	ds->line_len = ds->width / ds->side;
	if (ds->lines_count != 1)
		ds->gap = (ds->height - ds->lines_count * dt->ant_count * ds->side) /
				(ds->lines_count - 1);
	else
		ds->gap = 0;
	ds->h = dt->ant_count * ds->side * ds->lines_count + ds->gap * (ds->lines_count - 1);
}

int		ft_get_dims(t_data *dt)
{
	t_vis_dims	*ds;
	int 		free_space[2];

	if (!dt->real_nodes_count)
		ft_copy_nodes(dt);
	if (!(dt->dims = ft_memalloc(sizeof(t_vis_dims))))
		return (0);
	ds = dt->dims;
	ds->width = dt->screen_w - 2 * DEFAULT_H_PAD;
	ds->height = dt->screen_h - 2 * DEFAULT_V_PAD;
	ds->h = INF;



	ds->side = (int)sqrt((1. * ds->width * ds->height) / (dt->ant_count * dt->real_nodes_count));
	if (!ds->side)
		return (-1);
	ft_set_dims(dt);
	while (ds->side - 1 && (ds->h > ds->height || (ds->gap <= 0 && ds->lines_count != 1)))
	{
		--ds->side;
		ft_set_dims(dt);
	}
	free_space[0] = ds->width - (dt->real_nodes_count < ds->line_len ?
			dt->real_nodes_count : ds->line_len) * ds->side;
	free_space[1] = ds->height - dt->ant_count * ds->side * ds->lines_count;
	ds->gap = free_space[1] / 3;
	ds->h_pad = free_space[0] / 2;
	return (dt->dims->side ? 1 : -1);
}

void 	ft_fill_sorted_nodes(t_data *dt)
{
	int i;
	int len;
	int nodes_found_this_turn;
	int	dist;
	int	j;

	len = dt->nodes->len;
	dist = 0;
	nodes_found_this_turn = -1;
	j = 0;
	while (nodes_found_this_turn && (i = -1))
	{
		nodes_found_this_turn = 0;
		while (++i < len)
		{
			if (dt->dsts[i] == dist)
			{
				dt->sorted_nodes[j++] = (t_vis_node){i, dist / 2};
				++nodes_found_this_turn;
			}
		}
		dist += 2;
	}
	dt->real_nodes_count = j;
	dt->max_dst = (dist - 2) / 2;
}

void 	ft_fill_names_to_pos(t_data *dt)
{
	int i;
	int len;

	i = -1;
	len = dt->real_nodes_count;
	while (++i < len)
		dt->name_to_pos[dt->sorted_nodes[i].name] = i;
}

int 	ft_copy_nodes(t_data *dt)
{
	if (!(dt->sorted_nodes = ft_memalloc(sizeof(t_vis_node) * dt->nodes->len))
			|| !(dt->name_to_pos = ft_memalloc(sizeof(int) * dt->nodes->len)))
		return (0);
	ft_fill_sorted_nodes(dt);
	ft_fill_names_to_pos(dt);


	return (1);
}
