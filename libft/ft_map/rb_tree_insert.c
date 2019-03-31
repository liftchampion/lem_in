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

t_rb_tree		*rb_tree_create_node(void *key, t_rb_tree *parent,
											char is_less, t_map *map)
{
	t_rb_tree *new_node;

	new_node = (t_rb_tree*)malloc(sizeof(t_rb_tree) * 1);
	if (!new_node)
		return (0);
	map->size++;
	new_node->right = map->nil;
	new_node->left = map->nil;
	new_node->key = key;
	new_node->value = map->nil;
	new_node->color = RB_RED;
	new_node->parent = parent;
	if (is_less)
		parent->left = new_node;
	else if (parent)
		parent->right = new_node;
	return (new_node);
}

t_case			ft_check_rb_rules(t_rb_tree *new_node)
{
	t_rb_tree *uncle;

	if (!new_node || !new_node->parent || new_node->parent->color == RB_BLACK)
		return (GOOD);
	else
	{
		uncle = new_node->parent->parent->left;
		if (uncle == new_node->parent)
			uncle = new_node->parent->parent->right;
		if (uncle && uncle->color == RB_RED)
			return (REPAINT);
		else if (new_node->parent->parent->left == new_node->parent)
			if (new_node->parent->left == new_node)
				return (ROT_LL);
			else
				return (ROT_LR);
		else if (new_node->parent->left == new_node)
			return (ROT_RL);
		else
			return (ROT_RR);
	}
}

void			rb_tree_balance_insert(t_rb_tree *node, t_map *map)
{
	t_case res;

	while ((res = ft_check_rb_rules(node)) != GOOD)
	{
		if (res == REPAINT)
			node = ft_repaint(node);
		else if (res >= ROT_LL && res <= ROT_RR)
		{
			if (rb_tree_swap_colors(node, res) && res == ROT_LL)
				ft_rotate_right(node->parent->parent, map);
			else if (res == ROT_LR)
			{
				ft_rotate_left(node->parent, map);
				ft_rotate_right(node->parent, map);
			}
			else if (res == ROT_RL)
			{
				ft_rotate_right(node->parent, map);
				ft_rotate_left(node->parent, map);
			}
			else if (res == ROT_RR)
				ft_rotate_left(node->parent->parent, map);
			break ;
		}
	}
}

void			**rb_tree_insert_data(t_map *map, void *key)
{
	t_rb_tree	*current_node;
	t_rb_tree	*parent;
	int			cmp_res;

	if (!map->root)
	{
		if (!(map->root = rb_tree_create_node(key, 0, 0, map)))
			return (0);
		map->root->color = RB_BLACK;
		return (&(map->root->value));
	}
	current_node = map->root;
	while (current_node != map->nil)
	{
		cmp_res = map->info->cmp_f(key, current_node->key);
		if (!cmp_res)
			return (&(current_node->value));
		parent = current_node;
		current_node = cmp_res < 0 ? current_node->left : current_node->right;
	}
	current_node = rb_tree_create_node(key, parent, cmp_res < 0, map);
	if (!current_node)
		return (0);
	rb_tree_balance_insert(current_node, map);
	return (&(current_node->value));
}
