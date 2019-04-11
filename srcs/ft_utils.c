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

void		ft_print_parsed(t_data *dt)
{
	ft_printf("Ant-count: {Magenta}%d{eof}\n", dt->ant_count);
	ft_printf("Start: {Magenta}%d{eof}\n", dt->start);
	ft_printf("End:   {Magenta}%d{eof}\n", dt->end);
	int links_count = 0;
	for (size_t i = 0; i < dt->nodes->len; ++i)
	{
		t_node *nd = dt->nodes->data[i];
		ft_printf("{\\202}%-10s{eof} %d %d idx={Green}%d{eof}  p={Yellow}%d{eof}\n",
				nd->name, nd->x, nd->y,
				(int)*(void**)ft_map_get(dt->name_to_idx, nd->name),
				nd->p);
		ft_printf("\t\tc:< ");
		for (size_t j = 0; j < nd->chs->len; ++j)
		{
			links_count++;
			ft_printf("{Red}%d{eof}(%d) ",
					GET_I(nd->chs->data[j]), GET_W(nd->chs->data[j]));
		}
		ft_printf(">\n\t\tp:[ ");
		for (size_t j = 0; j < nd->prs->len; ++j)
			ft_printf("{Blue}%d{eof}(%d) ",
					GET_I(nd->prs->data[j]), GET_W(nd->prs->data[j]));
		ft_printf("]\n");
	}
	ft_printf("{\\200}Links count %d{eof}\n", links_count);
}

void		ft_print_path(t_data *dt, int mode)
{
	size_t *path;
	int len;
	int path_len;

	path = (size_t*)dt->path->data;
	len = dt->path->len;
	path_len = len;
	while (--len >= 0 && mode != 3)
	{
		if (mode == 2)
			ft_printf("%s (%d)\n", ((t_node*)dt->nodes->data[path[len]])->name, path[len]);
		if (mode == 1)
			ft_printf("%d\n", path[len]);
	}
	if (mode == 2 || mode == 3)
	{
		ft_printf("path len is: %d\n", path_len);
	}
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

void		ft_print_dijkstra(t_data *dt, int mode)
{
	if (mode == 1)
	{
		for (size_t i = 0; i < dt->nodes->len; ++i)
			ft_printf("%d\n", dt->dsts[i]);
	}
	if (mode == 2)
	{
		for (size_t i = 0; i < dt->nodes->len; ++i)
			ft_printf("%d: %d\n", i, dt->dsts[i]);
	}
}



