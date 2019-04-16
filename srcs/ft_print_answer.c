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

void	ft_print_ants(t_data *dt)
{
	int i;
	t_vector *paths;

	i = -1;
	paths = dt->flows->data[dt->best_flow];
	while (++i < dt->ant_count)
	{
		dt->ants[i].path = i % (dt->best_flow + 1);
	}
	ft_printf_ants2(dt);
	ft_print_murashi(dt);
}

void	ft_print_murashi(t_data *dt)
{
	int i;
	int start;
	int	pool;
	t_vector *paths;

	start = 0;
	pool = dt->best_flow + 1;
	paths = dt->flows->data[dt->best_flow];
	while (start != pool)
	{
		i = start - 1;
		while (++i < pool)
		{
			dt->ants[i].pos++;
			if (dt->ants[i].pos == (int)(((t_vector*)((t_vector*)dt->flows->data[dt->best_flow])->data[dt->ants[i].path])->len - 1))
			{
				++start;
			}
			ft_printf("L%d-%s ", i, ((t_node*)dt->nodes->data[(int)((t_vector*)paths->data[dt->ants[i].path])->data[((t_vector*)paths->data[dt->ants[i].path])->len - dt->ants[i].pos]])->name);
		}
		//ft_printf_ants2(dt);
		ft_printf("\n");
		pool = pool + dt->best_flow + 1;
		if (pool > dt->ant_count)
			pool = dt->ant_count;
		//pool = (pool + dt->best_flow + 1 > dt->ant_count ? dt->ant_count : pool + dt->best_flow + 1);
		//pool = (pool + dt->best_flow + 1 > dt->ant_count ? pool : pool + dt->best_flow + 1);
	}
}