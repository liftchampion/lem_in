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
#include "len_in.h"

void				dijkstra(t_data *graf)
{
	int				i;
	void			*j;
	register t_heap	*heap;
	register t_node	*node;
	size_t			vars[3];

	fill_heap(graf, (heap = graf->heap));
	while (heap->len && (i = -1))
	{
		vars[CN] = *heap->name;
		node = graf->nodes->data[vars[CN]];
		graf->dsts[vars[CN]] = take_min(graf->heap);
		while (++i < (int)node->chs->len && (j = node->chs->data[i]) >= 0)
		{
			if (graf->dsts[GET_I(j)] == NOT_VISITED &&
				*(int*)(vars[OLD] = (size_t)&heap->weight[heap->num[GET_I(j)]])
				> (int)(vars[NEW] = graf->dsts[vars[CN]] + node->p + GET_W(j) -
					((t_node*)graf->nodes->data[GET_I(j)])->p))
			{
				*(int*)vars[OLD] = vars[NEW];
				sift_up(heap, heap->num[GET_I(j)]);
			}
		}
	}
}
