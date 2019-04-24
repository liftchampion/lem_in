/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser_links.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggerardy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 11:02:01 by ggerardy          #+#    #+#             */
/*   Updated: 2019/04/10 11:02:01 by ggerardy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "len_in.h"

int		ft_add_link(int i1, int i2, t_data *dt)
{
	t_node *n1;
	t_node *n2;

	n1 = dt->nodes->data[i1];
	n2 = dt->nodes->data[i2];
	if (!ft_vector_push_back(&n1->chs, TO_EDGE(i2 + 1, 1)) ||
		!ft_vector_push_back(&n2->chs, TO_EDGE(i1 + 1, 1)))
		return (0);
	return (1);
}

int		ft_parse_link(char *ln, t_data *dt)
{
	char	*f_name;
	char	*s_name;
	int		i1;
	int		i2;

	if (*ln == '#')
		return (ft_parse_hash(dt, ln, LINKS));
	if (!(f_name = ft_strsub_char_m(&ln, '-', INIT_NAME_LEN)))
		return (0);
	if (*(ln++) != '-')
		return (free_ret(f_name, -1));
	if (!(s_name = ft_strsub_char_m(&ln, '\0', INIT_NAME_LEN)))
		return (free_ret(f_name, 0));
	if ((i1 = ft_find_in_map(f_name, dt)) < 0 ||
			(i2 = ft_find_in_map(s_name, dt)) < 0)
		return (free_ret(f_name, 0) + free_ret(s_name, -1));
	if (!ft_add_link(i1, i2, dt))
		return (free_ret(f_name, 0) + free_ret(s_name, 0));
	free(s_name);
	free(f_name);
	return (1);
}

int		ft_parse_links(t_data *dt, int fd)
{
	char	*ln;
	int		parse_res;

	while ((ln = (char*)1lu) && ft_get_next_line(fd, &ln, dt->buff_size))
	{
		if (!ln)
			return (0);
		if ((parse_res = ft_parse_link(ln, dt)) <= 0)
			return (free_ret(ln, parse_res));
		if (parse_res == 1 && (!ft_string_push_back_s(&dt->output, ln) ||
								!ft_string_push_back(&dt->output, '\n')))
			return (0);
		free(ln);
	}
	return (1);
}
