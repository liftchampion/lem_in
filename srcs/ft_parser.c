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

t_data	*ft_parser(int fd)
{
	t_data		*dt;
	int 		parse_res;

	if (!(dt = ft_make_data()))
		return (0);
	//ft_printf("{Red}1{eof}\n");
	if ((dt->ant_count = ft_parse_ants_count(fd)) <= 0)
		return ((void*)(size_t)ft_free_data(dt, 0));
	//ft_printf("{Red}2{eof}\n");
	if (!(parse_res = ft_parse_rooms(dt, fd)))
		return ((void*)(size_t)ft_free_data(dt, 0));
	//ft_printf("{Red}3{eof}\n");
	if (!ft_check_start_end(dt))
		return ((void*)(size_t)ft_free_data(dt, 0));
	//ft_printf("{Red}4{eof}\n");
	if (parse_res == -1)
		return (dt);
	//ft_printf("{Red}5{eof}\n");
	if (!ft_parse_links(dt, fd))
		return ((void*)(size_t)ft_free_data(dt, 0));
	//ft_printf("{Red}6{eof}\n");
	if (!(dt->heap = make_heap(dt->nodes->len)) ||
		!(dt->dsts = ft_memalloc(sizeof(int) * dt->nodes->len)))
		return ((void*)(size_t)ft_free_data(dt, 0));
	//ft_printf("{Red}7{eof}\n");
	//ft_upd_pts_sort_links(dt);
	return (dt);
}
