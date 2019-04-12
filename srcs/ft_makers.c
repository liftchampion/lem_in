/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_makers.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggerardy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 10:38:14 by ggerardy          #+#    #+#             */
/*   Updated: 2019/04/10 10:38:14 by ggerardy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "len_in.h"

t_node		*ft_make_node(void)
{
	t_node *node;

	if (!(node = ft_memalloc(sizeof(t_node))))
		return (0);
	if (!(node->chs = ft_make_vector(INIT_LINKS_FROM_NODE)))
		return ((void*)(size_t)free_ret(node, 0));
	return (node);
}

t_data		*ft_make_data(void)
{
	t_data		*dt;

	if (!(dt = ft_memalloc(sizeof(t_data))))
		return (0);
	if (!(dt->nodes = ft_make_vector(INIT_NODES_COUNT)) ||
		!(dt->name_to_idx = ft_make_std_map(NON_FREE_STR, INT32_T)) ||
		!(dt->path = ft_make_vector(INIT_PATH_LEN)) ||
		!(dt->flows = ft_make_vector(INIT_FLOW_COUNT)))
		return ((void*)(size_t)ft_free_data(dt, 0));
	dt->start = -1;
	dt->end = -1;
	return (dt);
}

t_heap				*make_heap(int len)
{
	t_heap	*heap;

	if (!(heap = (t_heap*)ft_memalloc(sizeof(t_heap))))
		return (0);
	if (!(heap->weight = (int*)malloc((size_t)len * 4)) ||
		!(heap->name = (int*)malloc((size_t)len * 4)) ||
		!(heap->num = (int*)malloc((size_t)len * 4)))
		return ((void*)(size_t)ft_free_heap(heap, 0));
	return (heap);
}
