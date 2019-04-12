/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flow.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggerardy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 16:48:29 by ggerardy          #+#    #+#             */
/*   Updated: 2019/04/11 16:48:29 by ggerardy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "len_in.h"

/*int 	ft_alloc_flows(t_data *dt, int max_size)
{
	int i;

	i = -1;
	while (++i)
	{

	}
}*/

int		ft_make_flows(t_data *dt, size_t max_size)
{
	size_t		begin;
	int			curr_flow;
	size_t		i;
	t_node		*nd;
	t_vector	*buf;

	if (!ft_alloc_flows(dt, max_size))
		return (0);
	buf = dt->path;
	buf->len = 0;
	ft_vector_push_back(&buf, (void*)(size_t)dt->start);
	begin = -1;
	curr_flow = 1;
	while (++begin != buf->len && (i = -1))
	{
		nd = dt->nodes->data[(int)buf->data[begin]];
		while (++i < max_size)
		{

		}
		i = -1;
		while (++i < nd->chs->len)
		{
			ft_vector_push_back(&buf, (void*)(size_t)GET_I(nd->chs->data[i]));
		}

	}
}

int		ft_find_all_flows(t_data *dt)
{
	int size;

	size = 0;
	dijkstra(dt);
	while (dt->dsts[dt->end] != INF)
	{
		ft_upd_pts(dt);
		if (!ft_find_shortest_path(dt))
			return (0);
		//ft_upd_pts(dt);
		if (!ft_send_flow(dt, size))
			return (0);
		//ft_find_shortest_path(dt);
		//ft_send_flow(dt);
		size++;
		dijkstra(dt);
	}
	dt->max_flow = size;
	ft_printf("Max flow is: %d\n", size);
	return (1);
}