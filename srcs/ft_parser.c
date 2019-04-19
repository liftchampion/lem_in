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

t_data	*ft_parser(int fd, t_pars *prs)
{
	t_data		*dt;
	int 		parse_res;

	if (!(dt = ft_make_data(prs)))
		return (0);
	dt->prs = prs;
	if ((dt->ant_count = ft_parse_ants_count(fd, dt)) <= 0)
		return ((void*)(size_t)ft_free_data(dt, 0));
	if (!(parse_res = ft_parse_rooms(dt, fd)))
		return ((void*)(size_t)ft_free_data(dt, 0));
	if (!ft_check_start_end(dt))
		return ((void*)(size_t)ft_free_data(dt, 0));
	if (parse_res == -1)
		return (dt + 0 * ft_get_next_line(fd, 0, dt->buff_size));
	if (!ft_parse_links(dt, fd))
		return ((void*)(size_t)ft_free_data(dt, 0));
	if (!(dt->heap = make_heap(dt->nodes->len)) ||
		!(dt->dsts = ft_memalloc(sizeof(int) * dt->nodes->len)) ||
		!(dt->ants = ft_memalloc(sizeof(t_ant) * dt->ant_count)) ||
		!(dt->gone_ants = ft_memalloc(dt->ant_count)) ||
		!ft_string_push_back(&dt->output, '\n') ||
		(GET_FMT_A(prs->flags) &&
		!(dt->output = ft_make_string(INIT_OUTPUT_SIZE))))
		return ((void*)(size_t)ft_free_data(dt, 0));
	return (dt + 0 * ft_get_next_line(fd, 0, dt->buff_size));
}
