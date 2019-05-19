/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shapka.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggerardy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 17:25:22 by ggerardy          #+#    #+#             */
/*   Updated: 2019/03/15 00:55:37 by ggerardy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_map.h"

void		rb_tree_merge(t_map *map1, t_rb_tree **tree2, t_map *map2,
						char free_second)
{
	if (!*tree2 || *tree2 == map2->nil)
	{
		return ;
	}
	rb_tree_insert_data(map1, (*tree2)->key);
	rb_tree_merge(map1, &((*tree2)->left), map2, free_second);
	rb_tree_merge(map1, &((*tree2)->right), map2, free_second);
	if (free_second == 'Y')
	{
		rb_tree_free_node(*tree2, map2);
		*tree2 = 0;
	}
}
