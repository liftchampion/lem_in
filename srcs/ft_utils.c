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

int 		ft_check_generator_flags(char *ln)
{
	if (!ft_strcmp(ln, "flow-one"))
		return (1);
	else if (!ft_strcmp(ln, "flow-ten"))
		return (1);
	else if (!ft_strcmp(ln, "flow-thousand"))
		return (1);
	else if (!ft_strcmp(ln, "big"))
		return (1);
	else if (!ft_strcmp(ln, "big-superposition"))
		return (1);
	return (0);
}
