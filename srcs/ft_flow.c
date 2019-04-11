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

int		ft_find_all_flows(t_data *dt)
{
	int size;

	size = 0;
	dijkstra(dt);
	//ft_upd_pts(dt);
	while (dt->dsts[dt->end] != INF)
	{
		ft_upd_pts(dt);
		if (!ft_find_shortest_path(dt))
			return (0);
		//ft_upd_pts(dt);
		if (!ft_send_flow(dt))
			return (0);
		//ft_find_shortest_path(dt);
		//ft_send_flow(dt);
		size++;
		dijkstra(dt);
	}
	ft_printf("Max flow is: %d\n", size);
	return (0);
}