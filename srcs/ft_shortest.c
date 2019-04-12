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
		curr_node = ((t_node*)dt->nodes->data[curr_node])->from;
	}
	ft_vector_push_back(&dt->path, (void*)(size_t)dt->start);
	return (dt->path ? 1 : 0);
}
