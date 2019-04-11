/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_shortest.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggerardy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 03:58:40 by ggerardy          #+#    #+#             */
/*   Updated: 2019/04/11 03:58:40 by ggerardy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "len_in.h"

static inline int	ft_find_min_parent(t_data *dt, const size_t *parents, int len)
{
	int i;
	int min_p;
	int min_i;
	int curr_p;
	int min_was_here;

	//int count = 0;

	i = -1;
	min_p = INF;
	min_i = INF;
	min_was_here = INF;
	while (++i < len)
	{
		curr_p = ((t_node*)dt->nodes->data[GET_I(parents[i])])->p;
		if (min_p > curr_p)
		{
			min_p = curr_p;
			min_i = GET_I(parents[i]);
			min_was_here = ((t_node*)dt->nodes->data[min_i])->was_here;
		}
		if (min_p == curr_p && min_was_here >
			((t_node*)dt->nodes->data[GET_I(parents[i])])->was_here)
		{
			min_p = curr_p;
			min_i = GET_I(parents[i]);
			min_was_here = ((t_node*)dt->nodes->data[min_i])->was_here;
			//ft_printf("BLYAAA! %d\n", ++count);
			//exit(0);
		}
	}
	return (min_i);
}

int		ft_find_shortest_path(t_data *dt)
{
	int curr_node;

	curr_node = dt->end;
	if (dt->dsts[curr_node] == INF)
		return (0);
	dt->path->len = 0;
	while (curr_node != dt->start)
	{
		++((t_node*)dt->nodes->data[curr_node])->was_here;
		t_node *nd = ((t_node*)dt->nodes->data[curr_node]);
		ft_printf("%d {Yellow}%d{eof} {Green}%d{eof}| ", curr_node, nd->p, nd->was_here);
		//if ((curr_node >= 1667 && curr_node <= 1671) || curr_node == 3652)
		//	exit(0);
		if (nd->p >= 44 && nd->p <= 48)
		{
			for (size_t i = 0; i < nd->prs->len; ++i)
			{
				if (nd->p == 44)
					ft_printf("{\\200}");
				else
					ft_printf("{Red}");
				ft_printf("%d(%d){Yellow}[%d] {eof}",
						GET_I(nd->prs->data[i]),
						GET_W(nd->prs->data[i]),
						((t_node*)dt->nodes->data[GET_I(nd->prs->data[i])])->p);
			}
		}
		if (nd->p == 47)
			ft_printf("\n");
		ft_printf("\n");
		ft_vector_push_back(&dt->path, (void*)(size_t)curr_node);
		curr_node = ft_find_min_parent(dt,
				(size_t*)((t_node*)dt->nodes->data[curr_node])->prs->data,
				((t_node*)dt->nodes->data[curr_node])->prs->len);
	}
	ft_vector_push_back(&dt->path, (void*)(size_t)dt->start);
	return (dt->path ? 1 : 0);
}
