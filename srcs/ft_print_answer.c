/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_answer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggerardy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 21:54:39 by ggerardy          #+#    #+#             */
/*   Updated: 2019/04/16 21:54:39 by ggerardy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "len_in.h"

int 	ft_fill_ants(t_data *dt)
{
	int i;
	int j;
	int k;
	int last_path;
	t_vector **paths;

	last_path = dt->best_flow + 1;
	paths = (t_vector**)((t_vector*)dt->flows->data[last_path - 1])->data;
	if (!(dt->wave_sizes = ft_memalloc(4 * (paths[0]->offset + paths[0]->len))))
		return (0);
	i = 0;
	k = 0;
	while (i < dt->ant_count && (j = -1))
	{
		while (++j < last_path && ++dt->wave_sizes[k])
		{
			dt->ants[i++].path = j;
			--(paths[j]->offset);
		}
		k++;
		last_path = 0;
		while (last_path <= dt->best_flow && paths[last_path]->offset)
			++last_path;
	}
	return (1);
}

int 	ft_push_ant_move(t_data *dt, int i, t_vector **paths)
{
	char	*str_tmp;

	if (dt->ant_names)
		ft_sprintf(&str_tmp, "L%s-%s ",
				dt->ant_names->data[i],
				((t_node*)dt->nodes->data[
				(int)paths[CURR_PATH]->data[PATH_LEN - CURR_POS]])->name);
	else
		ft_sprintf(&str_tmp, "L%d-%s ", i + 1, ((t_node *)dt->nodes->data[
			(int)paths[CURR_PATH]->data[PATH_LEN - CURR_POS]])->name);
	if (!str_tmp)
		return (0);
	if (!ft_string_push_back_s(&dt->output, str_tmp))
		return (0);
	free(str_tmp);
	return (1);
}

int		ft_print_murashi(t_data *dt)
{
	int i;
	int start;
	int	pool;
	int k;
	t_vector **paths;

	k = 0;
	start = 0;
	pool = dt->wave_sizes[k++];
	paths = (t_vector**)((t_vector*)dt->flows->data[dt->best_flow])->data;
	while (start != pool && (i = -1))
	{
		while (++i < pool && (++CURR_POS))
		{
			if (!dt->gone_ants[i])
				if (!ft_push_ant_move(dt, i, paths))
					return (0);
			if (CURR_POS == PATH_LEN && ++start)
				dt->gone_ants[i] = 1;
		}
		if (!ft_string_push_back(&dt->output + (++dt->turns) * 0, '\n'))
			return (0);
		pool += dt->wave_sizes[k++];
	}
	return (1);
}
