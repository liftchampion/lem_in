/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggerardy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 11:00:28 by ggerardy          #+#    #+#             */
/*   Updated: 2019/04/10 11:00:28 by ggerardy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "len_in.h"

int			ft_parse_ants_count(void)
{
	char *ln;
	int count;

	if (ft_get_next_line(FD, &ln, READ_BUFF) <= 0)
		return (0);
	if ((count = ft_atoi(ln)) <= 0)
		return (free_ret(ln, 0));
	if (ln[ft_intlen(count)])
		return (free_ret(ln, 0));
	return (free_ret(ln, count));
}

int		ft_parse_hash(t_data *dt, char *ln, t_parse_mode pm)
{
	if (ln[1] != '#' || pm == LINKS)
		return (1);
	if (!ft_strcmp("start", ln + 2))
	{
		if (dt->start != -1)
			return (0);
		dt->start = dt->nodes->len;
	}
	if (!ft_strcmp("end", ln + 2))
	{
		if (dt->end != -1)
			return (0);
		dt->end = dt->nodes->len;
	}
	return (1);
}

int 	ft_check_links_begin(char *end, t_node *nd, t_data *dt)
{
	char *ln;

	ln = end - 1 - ft_strlen(nd->name);
	ft_free_node(nd, 0);
	if (ft_strchr(ln, '-'))
		return (ft_parse_link(ln, dt) * -2);
	return (-1 * (dt->start == dt->end));
}

int 	ft_find_in_map(char *ln, t_data *dt)
{
	void	**map_value;

	if (!(map_value = ft_map_get(dt->name_to_idx, ln)) ||
			(*map_value) == dt->name_to_idx->nil)
		return (-1);
	return ((int)(*map_value));
}

int 	ft_check_start_end(t_data *dt)
{
	if (dt->start == -1 || dt->end == -1 ||
			dt->start >= (int)dt->nodes->len || dt->end >= (int)dt->nodes->len)
		return (0);
	return (1);
}
