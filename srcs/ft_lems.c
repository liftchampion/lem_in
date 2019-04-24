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

void		ft_send_lems_last_way(t_data *dt, int flow, int last_way,
									int ant_count)
{
	int			i;
	t_vector	*paths;
	int			len;
	int			wave_count;
	int			delta;

	paths = dt->flows->data[flow];
	len = ((t_vector*)paths->data[last_way])->len;
	i = -1;
	while (++i <= last_way && ant_count)
	{
		delta = (ant_count >= len - (int)((t_vector*)paths->data[i])->len + 1) ?
				len - ((t_vector*)paths->data[i])->len + 1 : ant_count;
		((t_vector*)paths->data[i])->offset = delta;
		ant_count -= delta;
	}
	wave_count = ant_count / (last_way + 1);
	ant_count -= wave_count * (last_way + 1);
	i = -1;
	while (++i <= last_way)
		((t_vector*)paths->data[i])->offset += wave_count;
	i = -1;
	while (++i <= last_way && ant_count--)
		((t_vector*)paths->data[i])->offset += 1;
}

int			ft_send_lems_one_flow(t_data *dt, int flow)
{
	int			lem_count;
	t_vector	*paths;

	ft_sort_paths_in_flow(dt, flow);
	lem_count = dt->ant_count;
	paths = dt->flows->data[flow];
	ft_send_lems_last_way(dt, flow, paths->len - 1, lem_count);
	return (((t_vector*)paths->data[0])->offset +
		((t_vector*)paths->data[0])->len - 1);
}
