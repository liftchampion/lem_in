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
	if (!(dt->wave_sizes = ft_memalloc(sizeof(int) * (paths[0]->offset + paths[0]->len - 1))))
		return (0);
	i = 0;
	k = 0;
	while (i < dt->ant_count && !(j = 0))
	{
		while (j < last_path)
		{
			dt->ants[i++].path = j;
			++dt->wave_sizes[k];
			--(paths[j]->offset);
			ft_printf("Ant %3d: path:%2d pos:%2d| offset: %d| wave: %d\n",
					i - 1, dt->ants[i - 1].path, dt->ants[i - 1].pos, paths[j]->offset, dt->wave_sizes[k]);
			++j;
		}
		k++;
		last_path = 0;
		while (last_path <= dt->best_flow && paths[last_path]->offset)
			++last_path;
	}


	return (1);
}


void	ft_print_ants(t_data *dt)
{
	int i;
	int j;
	int k;
	t_vector **paths;
	int best_flow;


	int wave_sum = 0;

	i = 0;
	k = 0;
	best_flow = dt->best_flow;
	paths = (t_vector**)((t_vector*)dt->flows->data[best_flow])->data;
	if (!(dt->wave_sizes = ft_memalloc(sizeof(int) * (paths[0]->offset + 50))))
		return ; // todo return 0
	while (i < dt->ant_count)
	{
		j = -1;
		//dt->wave_sizes[k] = best_flow;
		//wave_sum += dt->wave_sizes[k];
		while (++j <= best_flow)
		{
			//if (paths[j]->offset == 0)
			//{
			//	--best_flow;
			//	continue;
			//}
			++dt->wave_sizes[k];
			dt->ants[i].path = j;
			paths[j]->offset -= paths[j]->offset != 0;
			if (!paths[j]->offset)
				--best_flow;
			///ft_printf("Ant %3d: path:%2d pos:%2d| BF:%d| offset: %d| wave: %d\n",
			///		i, dt->ants[i].path, dt->ants[i].pos, best_flow,
			///		paths[j]->offset, dt->wave_sizes[k]);
			i++;

		}
		k++;
		//if (!--(paths[i % (best_flow + 1)]->offset))
		//	--best_flow;
		//dt->ants[i].path = i % (best_flow + 1);
	}

	for (int e = 0; e < k; e++)
	{
		wave_sum += dt->wave_sizes[e];
	}

	ft_printf("{Green}%d{eof}\n", wave_sum);
	//ft_printf_ants2(dt);
	ft_print_murashi(dt);
}

#define CURR_PATH dt->ants[i].path
#define CURR_POS dt->ants[i].pos
#define PATH_LEN (int)paths[CURR_PATH]->len

void	ft_print_murashi(t_data *dt)
{
	int i;
	int start;
	int	pool;
	int ants_who_go_in_this_wave;
	int k;
	t_vector **paths;

	k = 0;
	start = 0;
	pool = dt->wave_sizes[k++];
	paths = (t_vector**)((t_vector*)dt->flows->data[dt->best_flow])->data;
	while (start != pool && (i = -1))
	{
		//ft_printf("{Red}%d {Green}%d{eof}\n", pool, start);
		//i = start - 1;
		ants_who_go_in_this_wave = 0;
		while (++i < pool)
		{
			CURR_POS++;

			//int incriment_pool = dt->best_flow + 1;
			//int path_len = PATH_LEN;
			//int curr_pos = CURR_POS;
			//int curr_path = CURR_PATH;
			//int int_path_idx = PATH_LEN - CURR_POS;
			//int node_idx = (int)paths[CURR_PATH]->data[PATH_LEN - CURR_POS];
			if (CURR_POS == 1)
				ants_who_go_in_this_wave++;
			if (!dt->gone_ants[i])
				ft_printf("L%-3d-%4s ", i, ((t_node*)dt->nodes->data[(int)paths[CURR_PATH]->data[PATH_LEN - CURR_POS]])->name);
			if (CURR_POS == PATH_LEN && ++start)
				dt->gone_ants[i] = 1;
		}
		//ft_printf_ants2(dt);
		ft_printf("\n");
		pool += dt->wave_sizes[k++];
		//if (pool > dt->ant_count)
		//	pool = dt->ant_count;
		//pool = (pool + dt->best_flow + 1 > dt->ant_count ? dt->ant_count : pool + dt->best_flow + 1);
		//pool = (pool + dt->best_flow + 1 > dt->ant_count ? pool : pool + dt->best_flow + 1);
	}
}