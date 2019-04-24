/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_partitial_cases.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggerardy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 08:37:28 by ggerardy          #+#    #+#             */
/*   Updated: 2019/04/19 08:37:28 by ggerardy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "len_in.h"

int		ft_print_murashi_simple(t_data *dt)
{
	int		i;
	char	*tmp_line;
	char	*end_name;

	i = -1;
	end_name = ((t_node*)dt->nodes->data[dt->end - 1])->name;
	while (++i < dt->ant_count)
	{
		if (dt->prs->ant_names)
			ft_sprintf(&tmp_line, "L%s-%s ", dt->ant_names->data[i], end_name);
		else
			ft_sprintf(&tmp_line, "L%d-%s ", i + 1, end_name);
		if (!tmp_line)
			return (0);
		if (!ft_string_push_back_s(&dt->output, tmp_line))
			return (free_ret(tmp_line, 0));
		free(tmp_line);
	}
	if (!ft_string_push_back(&dt->output, '\n'))
		return (0);
	dt->turns = 1;
	return (1);
}

int		ft_procede_partitial_case(t_data *dt)
{
	int		i;
	void	**start_children;
	int		end;
	int		len;

	if (dt->start == dt->end - 1)
		return (1);
	i = -1;
	start_children = ((t_node*)dt->nodes->data[dt->start])->chs->data;
	len = ((t_node*)dt->nodes->data[dt->start])->chs->len;
	end = dt->end;
	while (++i < len)
	{
		if (GET_I(start_children[i]) == end)
			if (!ft_print_murashi_simple(dt))
				return (0);
	}
	return (dt->turns == 1 ? 2 : -1);
}
