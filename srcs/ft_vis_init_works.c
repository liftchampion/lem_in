/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vis_init_works.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggerardy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 10:55:41 by ggerardy          #+#    #+#             */
/*   Updated: 2019/04/24 10:55:41 by ggerardy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "len_in.h"

void				ft_add_unreaching_nodes(t_data *dt)
{
	int i;
	int j;
	int len;

	len = dt->nodes->len;
	i = -1;
	j = dt->real_nodes_count;
	while (++i < len)
	{
		if ((i + 1) % 2 && dt->dsts[i] == INF)
		{
			dt->sorted_nodes[j++] = (t_vis_node){i, INF};
		}
	}
	dt->real_nodes_count = j;
}

void				ft_fill_sorted_nodes(t_data *dt)
{
	int i;
	int len;
	int nodes_found_this_turn;
	int	dist;
	int	j;

	len = dt->nodes->len;
	dist = -2;
	nodes_found_this_turn = -1;
	j = 0;
	while (nodes_found_this_turn && (i = -1) && ((dist += 2) || 1))
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
	}
	dt->max_dst = (dist) / 2;
	dt->real_nodes_count = j;
	ft_add_unreaching_nodes(dt);
}

void				ft_rm_lines_from_output(t_data *dt)
{
	int			turns;
	t_string	*out;
	int			i;

	turns = dt->turns;
	if (!(out = dt->output))
		return ;
	i = 0;
	while (i <= turns && out->len > 0)
	{
		if (out->data[out->len - 1] == '\n')
			++i;
		--out->len;
	}
}

void				ft_fill_names_to_pos(t_data *dt)
{
	int i;
	int len;

	i = -1;
	len = dt->real_nodes_count;
	while (++i < len)
		dt->name_to_pos[dt->sorted_nodes[i].name] = i;
}

int					ft_copy_nodes(t_data *dt)
{
	if (!(dt->sorted_nodes = ft_memalloc(sizeof(t_vis_node) * dt->nodes->len))
			|| !(dt->name_to_pos = ft_memalloc(sizeof(int) * dt->nodes->len)))
		return (0);
	ft_fill_sorted_nodes(dt);
	ft_fill_names_to_pos(dt);
	return (1);
}
