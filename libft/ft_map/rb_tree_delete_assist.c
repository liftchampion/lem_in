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

t_color		rb_tree_delete_this_node(t_rb_tree *node, t_map *map,
						t_rb_tree *next, t_pair *data_to_free)
{
	t_color color;

	color = node->color;
	if (map->info->free_key_f)
		map->info->free_key_f(data_to_free->first);
	if (map->info->free_value_f)
		map->info->free_value_f(data_to_free->second);
	if (node->parent)
	{
		if (node->parent->right == node)
			node->parent->right = next;
		else
			node->parent->left = next;
	}
	else
	{
		map->root = next == map->nil ? 0 : next;
	}
	next->parent = node->parent;
	return (color);
}

void		b_tree_balance_delete_helper_red_bro_case(t_rb_tree *node,
						t_rb_tree **brother, t_map *map, char dir)
{
	(*brother)->color = RB_BLACK;
	node->parent->color = RB_RED;
	if (dir == 'L')
	{
		ft_rotate_left(node->parent, map);
		*brother = node->parent->right;
	}
	else
	{
		ft_rotate_right(node->parent, map);
		*brother = node->parent->left;
	}
}

void		rb_tree_balance_delete_helper_left(t_rb_tree **node,
										t_rb_tree *brother, t_map *map)
{
	if (brother->color == RB_RED)
		b_tree_balance_delete_helper_red_bro_case(*node, &brother, map, 'L');
	if (brother->left->color == RB_BLACK && brother->right->color == RB_BLACK)
	{
		brother->color = RB_RED;
		*node = (*node)->parent;
	}
	else
	{
		if (brother->right->color == RB_BLACK)
		{
			brother->left->color = RB_BLACK;
			brother->color = RB_RED;
			ft_rotate_right(brother, map);
			brother = (*node)->parent->right;
		}
		brother->color = (*node)->parent->color;
		(*node)->parent->color = RB_BLACK;
		brother->right->color = RB_BLACK;
		ft_rotate_left((*node)->parent, map);
		*node = map->root;
	}
}

void		rb_tree_balance_delete_helper_right(t_rb_tree **node,
									t_rb_tree *brother, t_map *map)
{
	if (brother->color == RB_RED)
	{
		b_tree_balance_delete_helper_red_bro_case(*node, &brother, map, 'R');
	}
	if (brother->right->color == RB_BLACK && brother->left->color == RB_BLACK)
	{
		brother->color = RB_RED;
		*node = (*node)->parent;
	}
	else
	{
		if (brother->left->color == RB_BLACK)
		{
			brother->right->color = RB_BLACK;
			brother->color = RB_RED;
			ft_rotate_left(brother, map);
			brother = (*node)->parent->left;
		}
		brother->color = (*node)->parent->color;
		(*node)->parent->color = RB_BLACK;
		brother->left->color = RB_BLACK;
		ft_rotate_right((*node)->parent, map);
		*node = map->root;
	}
}
