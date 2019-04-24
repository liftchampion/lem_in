/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vis_turns.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggerardy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 10:52:14 by ggerardy          #+#    #+#             */
/*   Updated: 2019/04/24 10:52:14 by ggerardy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "len_in.h"

#ifndef NO_VISUALIZATION

int					ft_turn_counter(t_data *dt, int turn)
{
	if (turn > 0 && dt->curr_turn >= dt->turns)
		return (0);
	if (turn < 0 && dt->curr_turn <= 0)
		return (0);
	dt->curr_turn += turn;
	return (1);
}

void				ft_print_turns(t_vector **paths, int i, t_data *dt)
{
	int		j;
	char	*end_name;

	if (dt->special_case == -1)
	{
		if (dt->ant_names)
			ft_printf("L%s-%s ", dt->ant_names->data[i],
					((t_node *)dt->nodes->data[
					(int)paths[CURR_PATH]->data[PATH_LEN - CURR_POS]])->name);
		else
			ft_printf("L%d-%s ", i + 1,
					((t_node *)dt->nodes->data[
					(int)paths[CURR_PATH]->data[PATH_LEN - CURR_POS]])->name);
	}
	else if (dt->special_case == 2 && (j = -1))
	{
		end_name = ((t_node*)dt->nodes->data[dt->end - 1])->name;
		while (++j < dt->ant_count)
			if (dt->prs->ant_names)
				ft_printf("L%s-%s ", dt->ant_names->data[j], end_name);
			else
				ft_printf("L%d-%s ", j + 1, end_name);
	}
}

void				ft_turn(t_data *dt, int turn)
{
	int			i;
	t_vector	**paths;

	paths = 0;
	if (dt->special_case == -1)
		paths = (t_vector**)((t_vector*)dt->flows->data[dt->best_flow])->data;
	if ((i = -1) && !ft_turn_counter(dt, turn))
		return ;
	while (++i < dt->ant_count)
	{
		dt->ants[i].pos += turn;
		if (turn == 1 && !GET_FMT_M(dt->prs->flags) && (dt->special_case > 0 ||
				(CURR_POS - 1 >= 0 && CURR_POS - 1 < PATH_LEN)))
			ft_print_turns(paths, i, dt);
	}
	ft_printf((turn == 1 && !GET_FMT_M(dt->prs->flags)) ? "\n\n" : "");
}

#endif
