/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggerardy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 10:42:59 by ggerardy          #+#    #+#             */
/*   Updated: 2019/04/10 10:42:59 by ggerardy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "len_in.h"

static inline void	ft_inl_swap(int *x, int *y, int h)
{
	h = *x;
	*x = *y;
	*y = h;
}

void				sift_down(t_heap *heap, int ind)
{
	int				len;
	register int	*weight;
	register int	*name;
	register int	next;
	int				help_var;

	help_var = 0;
	weight = heap->weight;
	name = heap->name;
	len = heap->len;
	while (len >= ind * 2)
	{
		next = (len < ind * 2 + 3 || LEFT < RIGHT ? ind * 2 + 1 : ind * 2 + 2);
		if (next < heap->len && weight[ind] > weight[next])
		{
			//ft_printf("{Green}+{eof}\n");
			heap->num[name[ind]] = next;
			heap->num[name[next]] = ind;
			ft_inl_swap(weight + ind, weight + next, help_var);
			ft_inl_swap(name + ind, name + next, help_var);
			ind = next;
		}
		else
			return ;
	}
}

void				sift_up(t_heap *heap, int ind)
{
	register int	*weight;
	register int	*name;
	int				help_var;
	int				next;

	help_var = 0;
	weight = heap->weight;
	name = heap->name;
	next = (ind - 1) / 2;
	while (weight[ind] < weight[next])
	{
		//ft_printf("{Green}-{eof}\n");
		heap->num[name[ind]] = next;
		heap->num[name[next]] = ind;
		ft_inl_swap(weight + ind, weight + next, help_var);
		ft_inl_swap(name + ind, name + next, help_var);
		ind = next;
		next = (ind - 1) / 2;
	}
}

int					take_min(t_heap *heap)
{
	int *name;
	int *weight;
	int len;
	int	help_var;
	int	r;

	help_var = 0;
	name = heap->name;
	weight = heap->weight;
	len = --(heap->len);
	r = *weight;
	heap->num[name[len]] = 0;
	//heap->num[*heap->name] = -1;
	ft_inl_swap(name + len, name, help_var);
	ft_inl_swap(weight + len, weight, help_var);

	//ft_printf("{Magenta}Before sift{eof}\n");
	//ft_printf("Heap: ");
	//for (int i = 0; i < heap->len; ++i)
	//ft_printf(" %2d", heap->weight[i]);
	//ft_printf("\nHeap place to name:");
	//for (int i = 0; i < heap->len; ++i)
	//ft_printf(" %2d", heap->name[i]);
	//ft_printf("\n");
	if (len > 1)
		sift_down(heap, 0);
	return (r);
}

void				fill_heap(t_data *graf, t_heap *heap)
{
	size_t	i;
	int		*weight;
	int		*name;
	int		*num;
	int		*dsts;

	weight = heap->weight;
	name = heap->name;
	num = heap->num;
	dsts = graf->dsts;
	i = graf->nodes->len;
	heap->len = (int)i;
	while (--i)
	{
		num[i] = (int)i;
		dsts[i] = NOT_VISITED;
		weight[i] = INF;
		name[i] = (int)i;
	}
	dsts[i] = NOT_VISITED;
	weight[i] = (int)i;
	name[i] = graf->start;
	num[i] = graf->start;
	name[graf->start] = (int)i;
	num[graf->start] = (int)i;
}
