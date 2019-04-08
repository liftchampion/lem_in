/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggerardy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 18:37:52 by ggerardy          #+#    #+#             */
/*   Updated: 2019/04/08 22:28:08 by ggerardy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "len_in.h"

int			ft_parse_ants_count(void)
{
	char *ln;
	int count;

	if (ft_get_next_line(0, &ln, READ_BUFF) <= 0)
		return (0);
	if ((count = ft_atoi(ln)) <= 0)
		return (free_ret(ln, 0));
	if (ln[ft_intlen(count)])
		return (free_ret(ln, 0));
	return (free_ret(ln, count));
}

int 	ft_parse_room(char *ln, t_data *dt)
{
	t_node *node;

	if (!(node = ft_memalloc(sizeof(t_node))))
		return (0);
	if (!(node->name = ft_strsub_char_m(&ln, ' ', 16)))
		return (0);
	++ln;
	node->x = ft_atoi_m(&ln);
	if (*ln != ' ')
		return (0);
	++ln;
	node->y = ft_atoi_m(&ln);
	if (*ln)
		return (0);
	if (!(ft_vector_push_back(&dt->nodes, node)))
		return (0);
	return (1);
}

int		ft_parse_rooms(t_data *dt)
{
	char *ln;

	while ((ln = (char*)1lu) && ft_get_next_line(0, &ln, READ_BUFF))
	{
		if (!ln)
			return (0);
		if (!ft_parse_room(ln, dt))
			return (free_ret(ln, 0));
		free(ln);
	}
	return (1);
}

t_vector	*ft_parser(void)
{
	t_data		*dt;

	if (!(dt = ft_memalloc(sizeof(t_data))))
		return (0);
	if (!(dt->nodes = ft_make_vector(128)) ||
		!(dt->name_to_idx = ft_make_std_map(STRING, INT32_T)))
		return ((void*)(size_t)ft_free_data(dt, 0));
	if ((dt->ant_count = ft_parse_ants_count()) <= 0)
		return ((void*)(size_t)ft_free_data(dt, 0));
	if (!ft_parse_rooms(dt))
		return ((void*)(size_t)ft_free_data(dt, 0));

	ft_print_parsed(dt);
	return (0);
}











