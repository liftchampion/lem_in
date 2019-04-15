/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lems.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggerardy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 17:24:39 by ggerardy          #+#    #+#             */
/*   Updated: 2019/04/15 17:24:39 by ggerardy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "len_in.h"

int		ft_send_lems_last_way(t_data *dt, int flow, int last_way, int ant_count)
{
	int		i;
	t_vector	*paths;
	int			len;
	int 		total;
	int 		wave_count;

	paths = dt->flows->data[flow];
	len = ((t_vector*)paths->data[last_way])->len;
	i = -1;
	total = 0;
	while (++i <= last_way)
	{
		total += len - ((t_vector*)paths->data[i])->len + 1;
		//((t_vector*)paths->data[i])->offset +=
		//		len - ((t_vector*)paths->data[i])->len + 1;
	}
	///ft_printf("{Blue}Total is %d{eof}\n", total);
	wave_count = ant_count / total;
	///ft_printf("{Blue}Wave count is %d{eof}\n", wave_count);
	///ft_printf("{Blue}Max len is %d{eof}\n", len);
	i = -1;
	while (++i <= last_way)
	{
		((t_vector*)paths->data[i])->offset +=
				(len - ((t_vector*)paths->data[i])->len + 1) * wave_count;
	}
	return (ant_count - total * wave_count);
}

int 	ft_send_lems_one_flow(t_data *dt, int flow)
{
	int lem_count;
	int time;
	t_vector *paths;
	int last_way;

	lem_count = dt->ant_count;
	paths = dt->flows->data[flow];
	last_way = paths->len - 1;
	while (lem_count && last_way)
	{
		///ft_printf("Lem count %d\n", lem_count);
		lem_count = ft_send_lems_last_way(dt, flow, last_way--, lem_count);
	}
	//ft_print_flows(dt, 2);
	////ft_printf("Lem count %d (after while)\n", lem_count);
	((t_vector*)paths->data[0])->offset += lem_count;
	//ft_print_flows(dt, 2);
	time = ((t_vector*)paths->data[0])->offset + ((t_vector*)paths->data[0])->len - 1;
	////ft_printf("Flow %d time is {Green}%d{eof}\n", flow + 1, time);
	return (time);
}

int 	ft_send_lems(t_data *dt)
{
	size_t	i;
	int 	best_flow_time;
	int 	best_flow;
	int 	curr_flow_time;

	i = (size_t)-1;
	best_flow_time = INF;
	best_flow = INF;
	while (++i < dt->flows->len)
	{
		////ft_printf("{Red}Curr flow %d{eof}\n", i + 1);
		curr_flow_time = ft_send_lems_one_flow(dt, i);
		if (curr_flow_time < best_flow_time)
		{
			best_flow = i;
			best_flow_time = curr_flow_time;
		}
		ft_printf("Curr flow is: {\\202}%d{eof}. Time is: {\\200}%d{eof}\n",
				i + 1, curr_flow_time);
	}
	ft_printf("{Green}Best{eof} flow is: {\\202}%d{eof}. Time is: {\\200}%d{eof}\n",
			best_flow + 1, best_flow_time);
	return (best_flow);
}