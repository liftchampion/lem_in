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

void		ft_print_parsed(t_data *dt)
{
	ft_printf("Ant-count: {Magenta}%d{eof}\n", dt->ant_count);
	ft_printf("Start: {Magenta}%d{eof}\n", dt->start);
	ft_printf("End:   {Magenta}%d{eof}\n", dt->end);
	int links_count = 0;
	for (size_t i = 0; i < dt->nodes->len; ++i)
	{
		t_node *nd = dt->nodes->data[i];
		ft_printf("{\\202}%-10s{eof} %d %d idx={Green}%d{eof}\n", nd->name, nd->x, nd->y,
				(int)*(void**)ft_map_get(dt->name_to_idx, nd->name));
		ft_printf("\t\tc:< ");
		for (size_t j = 0; j < nd->children->len; ++j)
		{
			links_count++;
			ft_printf("{Red}%d{eof}(%d) ",
					GET_I(nd->children->data[j]), GET_W(nd->children->data[j]));
		}
		ft_printf(">\n\t\tp:[ ");
		for (size_t j = 0; j < nd->parents->len; ++j)
			ft_printf("{Blue}%d{eof}(%d) ",
					GET_I(nd->parents->data[j]), GET_W(nd->parents->data[j]));
		ft_printf("]\n");
	}
	ft_printf("{\\200}Links count %d{eof}\n", links_count);
}

void		ft_print_heap(t_data *dt)
{
	t_heap *heap;

	heap = dt->heap;
	ft_printf("Dij: ");
	for (size_t i = 0; i < dt->nodes->len; ++i)
		ft_printf(" %2d", dt->dsts[i]);
	ft_printf("\nHeap: ");
	for (int i = 0; i < heap->len; ++i)
		ft_printf(" %2d", heap->weight[i]);
	ft_printf("\nHeap place to name:");
	for (int i = 0; i < heap->len; ++i)
		ft_printf(" %2d", heap->name[i]);
	ft_printf("\nHeap name to place:");
	for (size_t i = 0; i < dt->nodes->len; ++i)
		ft_printf(" %2d", heap->num[i]);
	ft_printf("\n");
}

void		ft_print_dijkstra(t_data *dt)
{
	for (size_t i = 0; i < dt->nodes->len; ++i)
		ft_printf("%d\n", dt->dsts[i]);
}



