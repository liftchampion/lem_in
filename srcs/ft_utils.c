/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggerardy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 19:50:42 by ggerardy          #+#    #+#             */
/*   Updated: 2019/04/08 22:10:45 by ggerardy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "len_in.h"
#include "lem_in_structs.h"

static inline void	ft_inl_swap(void **x, void **y)
{
	void *h;

	h = *x;
	*x = *y;
	*y = h;
}

void		ft_upd_pts(t_data *dt)
{
	int i;
	int len;
	int *p;
	int dst;

	len = dt->nodes->len;
	i = -1;
	while (++i < len)
	{
		p = &((t_node*)dt->nodes->data[i])->p;
		dst = dt->dsts[i];
		if (*p == INF || dst == INF)
			*p = INF;
		else
			*p += dst;
	}
}

void		ft_sort_paths_in_flow(t_data *dt, int flow)
{
	size_t j;
	size_t k;
	t_vector *curr_flow;

	curr_flow = dt->flows->data[flow];
	j = (size_t)-1;
	while (++j < curr_flow->len)
	{
		k = j - 1;
		while (++k < curr_flow->len)
		{
			if (((t_vector*)curr_flow->data[k])->len <
					((t_vector*)curr_flow->data[j])->len)
				ft_inl_swap(curr_flow->data + j, curr_flow->data + k);
		}
	}
}

void		ft_print_flows(t_data *dt, int mode)
{
	t_vector *flows;
	t_vector *curr_flow;
	t_vector *curr_path;

	flows = dt->flows;

	ft_printf("Flows count: %d\n", (int)flows->len);
	for (size_t i = 0; i < flows->len; ++i)
	{
		ft_printf("~~~~~~~~~~~~~~~~~~~~~~ %2d ~~~~~~~~~~~~~~~~~~~~~~\n", i + 1);
		curr_flow = flows->data[i];
		for (size_t j = 0; j < curr_flow->len; ++j)
		{
			ft_printf("%2d: ", j + 1);
			curr_path = curr_flow->data[j];
			if (mode == 1)
			{
				for (size_t k = 0; k < curr_path->len; ++k)
				{
					int idx = (int)curr_path->data[k];
					ft_printf("%s ", ((t_node *)dt->nodes->data[idx])->name);
				}
				ft_printf("\n");
			}
			if (mode == 2)
			{
				ft_printf("%d({Yellow}%d{eof})\n",
						(int)curr_path->len,
						curr_path->offset);
			}
		}
		ft_printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	}
}

