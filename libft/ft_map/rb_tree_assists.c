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

void			rb_tree_free_node(t_rb_tree *node, t_map *map)
{
	if (map->info->free_key_f)
		map->info->free_key_f(node->key);
	if (map->info->free_value_f)
		map->info->free_value_f(node->value);
	free(node);
}

void			rb_tree_free(t_rb_tree **tree, t_map *map)
{
	if (!*tree || *tree == map->nil)
	{
		return ;
	}
	rb_tree_free(&((*tree)->left), map);
	rb_tree_free(&((*tree)->right), map);
	rb_tree_free_node(*tree, map);
	*tree = 0;
}

t_rb_tree		*rb_tree_find_min(t_rb_tree *node, t_rb_tree *nil)
{
	while (node->left != nil)
	{
		node = node->left;
	}
	return (node);
}

t_rb_tree		*rb_tree_find_max(t_rb_tree *node, t_rb_tree *nil)
{
	while (node->right != nil)
	{
		node = node->right;
	}
	return (node);
}
