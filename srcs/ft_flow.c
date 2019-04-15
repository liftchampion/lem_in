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


static inline int	ft_find_next(t_data *dt, int from)
{
	void 	**starts;
	int 	i;
	int 	len;

	starts = ((t_node*)dt->nodes->data[from])->chs->data;
	len = ((t_node*)dt->nodes->data[from])->chs->len;
	i = -1;
	while (++i < len)
	{
		if (GET_W(starts[i]) == -1)
			return (GET_I(starts[i]));
	}
	return (INF); // todo for segfault
}

int 	ft_restore_path(t_data *dt, int from, t_vector **path)
{
	int		curr_node;
	int		finish;

	curr_node = from;
	finish = dt->start;
	while (curr_node != finish)
	{
		curr_node = ft_find_next(dt, curr_node);
		if (curr_node % 2 == 0 && curr_node != dt->start)
		{
			if (!ft_vector_push_back(path, (void *)(size_t)curr_node))
				return (0);
		}
	}
	return (1);
}

int		ft_restore_flow(t_data *dt)
{
	int			i;
	void		**starts;
	t_vector	*flow;
	t_vector	*path;
	int 		len;

	if (!(flow = ft_make_vector(INIT_LINKS_FROM_NODE)))
		return (0);
	path = 0;
	i = -1;
	len = ((t_node*)dt->nodes->data[dt->end])->chs->len;
	starts = ((t_node*)dt->nodes->data[dt->end])->chs->data;
	while (++i < len)
	{
		if (GET_W(starts[i]) == -1 &&
			(!(path = ft_make_vector(INIT_PATH_LEN)) ||
			!ft_vector_push_back(&path, (void*)(size_t)dt->end - 1) ||
			!ft_vector_push_back(GET_I(starts[i]) == dt->start ? 0 : &path,
					(void*)(size_t)GET_I(starts[i])) ||
			!ft_restore_path(dt, GET_I(starts[i]), &path) ||
			!ft_vector_push_back(&flow, path)))
			return (ft_free_ret_vector(&path, 0) +
					ft_free_ret_vector(&flow, 0)); // todo free flow by special function
	}
	ft_vector_push_back(&dt->flows, flow);
	return (dt->flows ? 1 : 0);
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
		if (!ft_send_flow(dt))
			return (0);
		ft_restore_flow(dt);
		//ft_find_shortest_path(dt);
		//ft_send_flow(dt);
		size++;
		dijkstra(dt);
	}
	dt->max_flow = size;
	ft_printf("Max flow is: %d\n", size);
	return (1);
}