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
