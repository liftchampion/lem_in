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

int 	ft_alloc_flows(t_data *dt, int max_size)
{
	int i;
	int j;

	if (!(dt->flows = ft_memalloc(max_size * sizeof(void*))))
		return (0);
	i = 0;
	while (++i <= max_size && (j = -1))
	{
		if (!(dt->flows[i - 1] = ft_make_vector(INIT_FLOW_COUNT)))
			return (0); // TODO free
	}
	return (1);
}

int 	ft_restore_path(t_data *dt, int start, int flow)
{
	int curr_node;
	int finish;
	size_t j;
	t_vector *bros;
	t_vector *path;

	path = 0;
	curr_node = start;
	finish = dt->end;
	j = -1;
	while (curr_node != finish)
	{
		++j;
		bros = ((t_node*)dt->nodes->data[curr_node])->bros;
		/*ft_printf("Looking from %s to %s\n",
				((t_node*)dt->nodes->data[curr_node])->name,
				((t_node*)dt->nodes->data[(int)bros->data[j]])->name);*/
		/*tt u;
		u.ui = dt->nd_to_flow[(int)bros->data[j]];
		ft_printf(">>%#llB\n", u.ll[1]);
		u.ui = ((__uint128_t)1 << (127u - (unsigned)flow));
		ft_printf(">>%#llB\n", u.ll[1]);
		u.ui = dt->nd_to_flow[(int)bros->data[j]] & ((__uint128_t)1 << (127u - (unsigned)flow));
		ft_printf(">>%#llB\n\n", u.ll[1]);*/
		if (j >= bros->len)
			curr_node = finish;
		else if (dt->nd_to_flow[(int)bros->data[j]] & ((__uint128_t)1 << (127u - (unsigned)flow)))
		{
			if (!path && (!(path = ft_make_vector(INIT_PATH_LEN))))
				return (0);
			if (!ft_vector_push_back(&path, (void*)(size_t)curr_node))
				return (0);
			dt->nd_to_flow[curr_node] &= ~((__uint128_t)1 << (127u - (unsigned)flow));
			curr_node = (int)bros->data[j];
			ft_printf("CURR NODE  %s\n", ((t_node*)dt->nodes->data[curr_node])->name);
			j = -1;
		}

	}
	ft_vector_push_back(&path, (void*)(size_t)finish);
	ft_vector_push_back(&dt->flows[flow], path);
	return (dt->flows[flow] ? 1 : 0);
}

int 	ft_restore_paths(t_data *dt, int start)
{
	int			i;
	int			max_flow;
	__uint128_t	flags;

	i = -1;
	max_flow = dt->max_flow;
	flags = dt->nd_to_flow[start];
	while (++i < max_flow)
	{
		if (flags & ((__uint128_t)1 << (unsigned)i))
		{
			ft_printf("Restoring path for flow {Yellow}%d{eof}\n", i + 1);
			if (!ft_restore_path(dt, start, i))
				return (0);
		}
	}

	return (1);
}

int		ft_make_flows(t_data *dt, size_t max_size)
{
	size_t i;
	t_vector *starts;

	ft_printf("{Red}Flows count: %d{eof}\n", dt->max_flow);
	if (!ft_alloc_flows(dt, max_size))
		return (0);
	i = (size_t)-1;
	starts = ((t_node*)dt->nodes->data[dt->start])->bros;
	while (++i < starts->len)
	{
		ft_printf("{Blue}Looking to start: %s{eof}\n", ((t_node*)dt->nodes->data[(int)starts->data[i]])->name);
		if (!ft_restore_paths(dt, (int)starts->data[i]))
			return (0);
		ft_printf("Finished: this\n");
	}

	return (1);
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