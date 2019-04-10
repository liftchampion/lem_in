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
	int		i;
	void	*j;
	t_heap	*heap;
	t_node	*node;

	heap = graf->heap;
	fill_heap(graf);
	//ft_print_heap(graf);
	while (heap->len)
	{
		i = *heap->name;
		int tmp = i; // todo
		node = graf->nodes->data[i];
		/*ft_printf("{Red}Eject min %s(%d){eof}\n",
				((t_node*)graf->nodes->data[tmp])->name,
				tmp);*/
		graf->dsts[i] = take_min(graf->heap);
		i = -1;
		//ft_print_heap(graf);
		while (++i < (int)node->children->len)
		{
			j = node->children->data[i];
			if (graf->dsts[GET_I(j)] == -57)
			{
				heap->weight[heap->num[GET_I(j)]] = graf->dsts[tmp] + node->p + GET_W(j) -
					((t_node *)graf->nodes->data[GET_I(j)])->p;
				/*ft_printf("{Blue}Upd dst from %s(%d) to %s(%d){eof}\n",
						((t_node*)graf->nodes->data[tmp])->name,
						tmp,
						((t_node*)graf->nodes->data[GET_I(j)])->name,
						GET_I(j));*/
				sift_up(heap, heap->num[GET_I(j)]);
				//ft_print_heap(graf);
			}
		}
	}
}
