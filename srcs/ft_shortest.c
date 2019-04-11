/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_shortest.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggerardy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 03:58:40 by ggerardy          #+#    #+#             */
/*   Updated: 2019/04/11 03:58:40 by ggerardy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "len_in.h"

int 	ft_find_min_parent(t_data *dt, const size_t *parents, int len)
{
	int i;
	int min_p;
	int min_i;
	int curr_p;

	i = -1;
	min_p = INF;
	min_i = INF;
	while (++i < len)
	{
		curr_p = ((t_node*)dt->nodes->data[GET_I(parents[i])])->p;
		if (min_p > curr_p)
		{
			min_p = curr_p;
			min_i = GET_I(parents[i]);
		}
	}
	return (min_i);
}

int		ft_find_shortest_path(t_data *dt)
{
	int curr_node;

	curr_node = dt->end;
	if (dt->dsts[curr_node] == INF)
		return (0);
	dt->path->len = 0;
	while (curr_node != dt->start)
	{
		ft_vector_push_back(&dt->path, (void*)(size_t)curr_node);
		curr_node = ft_find_min_parent(dt,
				(size_t*)((t_node*)dt->nodes->data[curr_node])->prs->data,
				((t_node*)dt->nodes->data[curr_node])->prs->len);
	}
	ft_vector_push_back(&dt->path, (void*)(size_t)dt->start);
	return (dt->path ? 1 : 0);
}
