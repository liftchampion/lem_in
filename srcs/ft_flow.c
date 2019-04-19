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
	return (INF);
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

int 	ft_flow_push_backs(t_data *dt, t_vector **flow, void **starts, int idx)
{
	t_vector	*path;

	path = 0;
	if (!(path = ft_make_vector(INIT_PATH_LEN)) ||
		!ft_vector_push_back(&path, (void*)(size_t)dt->end - 1) ||
		!ft_vector_push_back(GET_I(starts[idx]) == dt->start ? 0 : &path,
							(void*)(size_t)GET_I(starts[idx])) ||
		!ft_restore_path(dt, GET_I(starts[idx]), &path) ||
		!ft_vector_push_back(flow, path))
		return (ft_free_ret_vector(&path, 0) + ft_free_ret_vector(flow, 0));
	return (1);
}

int		ft_restore_flow(t_data *dt)
{
	int			i;
	void		**starts;
	t_vector	*flow;
	int 		len;

	if (!(flow = ft_make_vector_free(INIT_LINKS_FROM_NODE,
			ft_free_vector_simple)))
		return (0);
	i = -1;
	len = ((t_node*)dt->nodes->data[dt->end])->chs->len;
	starts = ((t_node*)dt->nodes->data[dt->end])->chs->data;
	while (++i < len)
	{
		if (GET_W(starts[i]) == -1 && !ft_flow_push_backs(dt, &flow, starts, i))
			return (0);
	}
	ft_vector_push_back(&dt->flows, flow);
	return (dt->flows ? 1 : 0);
}

int		ft_find_all_flows(t_data *dt)
{
	int size;
	int best_fl_tm;
	int curr_fl_tm;

	size = 0;
	best_fl_tm = INF;
	dijkstra(dt); // todo if VIZ copy result somewhere
	while (dt->dsts[dt->end] != INF)
	{
		ft_upd_pts(dt);
		if (!ft_find_shortest_path(dt) || !ft_send_flow(dt) ||
			!ft_restore_flow(dt))
			return (0);
		if ((curr_fl_tm = ft_send_lems_one_flow(dt, size)) > best_fl_tm)
			break ;
		if (curr_fl_tm < best_fl_tm && (best_fl_tm = curr_fl_tm))
			dt->best_flow = size;
		size++;
		dijkstra(dt);
	}
	return (size ? 1 : 0);
}