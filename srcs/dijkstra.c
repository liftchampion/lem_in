/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dijkstra.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmiklaz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 18:39:09 by bmiklaz           #+#    #+#             */
/*   Updated: 2019/04/08 18:39:16 by bmiklaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in_structs.h"

/*static inline void	ft_inl_swap(int *x, int *y, int h)
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

	weight = heap->weight;
	name = heap->name;
	len = heap->len;
	while (len >= ind * 2)
	{
		next = (len < ind * 2 + 3 || LEFT < RIGHT ? ind * 2 + 1 : ind * 2 + 2);
		if (weight[ind] > weight[next])
		{
			ft_inl_swap(weight + ind, weight + next, help_var);
			ft_inl_swap(name + ind, name + next, help_var);
			heap->num[name[ind]] = ind;
			heap->num[name[next]] = next;
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

	weight = heap->weight;
	name = heap->name;
	while (weight[ind] < weight[(ind - 1) / 2])
	{
		next = (ind - 1) / 2;
		ft_inl_swap(weight + ind, weight + next, help_var);
		ft_inl_swap(name + ind, name + next, help_var);
		heap->num[name[ind]] = ind;
		heap->num[name[next]] = next;
		ind = next;
	}
}

int					take_min(t_heap *heap)
{
	int *name;
	int *weight;
	int len;
	int	help_var;
	int	r;

	name = heap->name;
	weight = heap->weight;
	len = --(heap->len);
	r = *weight;
	ft_inl_swap(name + len, name, help_var);
	ft_inl_swap(weight + len, weight, help_var);
	sift_down(heap, 0);
	return (r);
}

t_heap				*make_heap(int len)
{
	t_heap	*heap;

	heap = (t_heap*)malloc(sizeof(t_heap));
	heap->weight = (int*)malloc((size_t)len * 4);
	heap->name = (int*)malloc((size_t)len * 4);
	heap->num = (int*)malloc((size_t)len * 4);
	return (heap);
}

void				fill_heap(t_data *graf)
{
	size_t	i;
	int		*weight;
	int		*name;
	int		*num;
	int		*dsts;

	weight = graf->heap->weight;
	name = graf->heap->name;
	num = graf->heap->num;
	dsts = graf->dsts;
	i = graf->nodes->len;
	graf->heap->len = (int)i;
	while (--i)
	{
		num[i] = (int)i;
		dsts[i] = -57;
		weight[i] = 1000000;
		name[i] = (int)i;
	}
	dsts[i] = -57;
	weight[i] = (int)i;
	name[i] = graf->start;
	num[i] = graf->start;
	name[graf->start] = (int)i;
	num[graf->start] = (int)i;
}*/
/*
void				dijkstra(t_data *graf)
{
	int		i;
	t_heap	*heap;
	t_node	*node;

	heap = graf->heap;
	fill_heap(graf);
	while (heap->len)
	{graf->
		i = -1;
		node = *heap->name
		graf->dsts[*heap->name] = take_min(graf->heap);
		while (++i < graf->nodes->len)
	}
}*/
