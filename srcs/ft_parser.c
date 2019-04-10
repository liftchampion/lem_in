/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggerardy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 18:37:52 by ggerardy          #+#    #+#             */
/*   Updated: 2019/04/09 18:21:08 by ggerardy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "len_in.h"

t_data	*ft_parser(void)
{
	t_data		*dt;
	int 		parse_res;

	if (!(dt = ft_make_data()))
		return (0);
	if ((dt->ant_count = ft_parse_ants_count()) <= 0)
		return ((void*)(size_t)ft_free_data(dt, 0));
	if (!(parse_res = ft_parse_rooms(dt)))
		return ((void*)(size_t)ft_free_data(dt, 0));
	if (!ft_check_start_end(dt))
		return ((void*)(size_t)ft_free_data(dt, 0));
	if (parse_res == -1)
		return (dt);
	if (!ft_parse_links(dt))
		return ((void*)(size_t)ft_free_data(dt, 0));
	if (!(dt->heap = make_heap(dt->nodes->len)) ||
		!(dt->dsts = malloc(sizeof(int) * dt->nodes->len)))
		return ((void*)(size_t)ft_free_data(dt, 0));
	return (dt);
}
