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

void			rb_tree_balance_delete(t_rb_tree *node, t_map *map)
{
	while (node->parent && node->color == RB_BLACK)
	{
		if (node == node->parent->left)
		{
			rb_tree_balance_delete_helper_left(&node, node->parent->right, map);
		}
		else
		{
			rb_tree_balance_delete_helper_right(&node, node->parent->left, map);
		}
	}
	node->color = RB_BLACK;
}

t_pair			rb_tree_delete_node(t_rb_tree *node, t_map *map)
{
	t_rb_tree	*child;
	t_pair		data_to_free;

	data_to_free = (t_pair){node->key, node->value};
	while (1)
	{
		if (node->left == map->nil && node->right == map->nil)
		{
			return ((t_pair){(void*)(size_t)rb_tree_delete_this_node(node, map,
					map->nil, &data_to_free), (void*)node});
		}
		else if (node->left == map->nil || node->right == map->nil)
		{
			child = node->left != map->nil ? node->left : node->right;
			return ((t_pair){(void*)(size_t)rb_tree_delete_this_node(node, map,
					child, &data_to_free), (void*)node});
		}
		else
		{
			child = rb_tree_find_max(node->left, map->nil);
			node->key = child->key;
			node->value = child->value;
			node = child;
		}
	}
}

void			rb_tree_delete_key(t_map *map, void *key)
{
	t_rb_tree	*current_node;
	t_pair		color_n_node;
	int			cmp_res;

	if (!map || !map->root)
		return ;
	current_node = map->root;
	while (current_node != map->nil)
	{
		cmp_res = map->info->cmp_f(key, current_node->key);
		if (cmp_res < 0)
			current_node = current_node->left;
		else if (cmp_res > 0)
			current_node = current_node->right;
		else
		{
			color_n_node = rb_tree_delete_node(current_node, map);
			if ((char)color_n_node.first == RB_BLACK)
				rb_tree_balance_delete(((t_rb_tree*)color_n_node.second)->right
						== map->nil ? ((t_rb_tree*)color_n_node.second)->left :
						((t_rb_tree*)color_n_node.second)->right, map);
			map->size--;
			return (free(color_n_node.second));
		}
	}
}
