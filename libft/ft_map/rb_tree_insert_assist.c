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

t_relatives		ft_get_relatives(t_rb_tree *root)
{
	t_relatives res;

	if (!root)
		return (t_relatives){0, 0, 0};
	if (!root->parent)
	{
		res.father = 0;
		res.grandfather = 0;
		res.uncle = 0;
	}
	else if (!root->parent->parent)
	{
		res.father = root->parent;
		res.grandfather = 0;
		res.uncle = 0;
	}
	else
	{
		res.father = root->parent;
		res.grandfather = root->parent->parent;
		res.uncle = root->parent->parent->left;
		if (res.uncle == root->parent)
			res.uncle = root->parent->parent->right;
	}
	return (res);
}

t_rb_tree		*ft_repaint(t_rb_tree *node)
{
	t_relatives relatives;

	relatives = ft_get_relatives(node);
	if (relatives.uncle)
		relatives.uncle->color = RB_BLACK;
	if (relatives.father)
		relatives.father->color = RB_BLACK;
	if (relatives.grandfather)
	{
		relatives.grandfather->color = relatives.grandfather->parent ?
								RB_RED : RB_BLACK;
	}
	return (relatives.grandfather);
}

int				rb_tree_swap_colors(t_rb_tree *node, t_case tree_case)
{
	t_color tmp;

	if (tree_case == ROT_LL || tree_case == ROT_RR)
	{
		tmp = node->parent->color;
		node->parent->color = node->parent->parent->color;
		node->parent->parent->color = tmp;
		return (1);
	}
	if (tree_case == ROT_LR || tree_case == ROT_RL)
	{
		tmp = node->color;
		node->color = node->parent->parent->color;
		node->parent->parent->color = tmp;
	}
	return (1);
}

void			ft_rotate_right(t_rb_tree *father, t_map *map)
{
	t_rb_tree *left_son;

	left_son = father->left;
	father->left = left_son->right;
	if (father->left != map->nil)
		father->left->parent = father;
	left_son->parent = father->parent;
	if (father->parent == 0)
	{
		map->root = left_son;
		map->root->color = RB_BLACK;
	}
	else if (father == father->parent->right)
		father->parent->right = left_son;
	else
		father->parent->left = left_son;
	left_son->right = father;
	father->parent = left_son;
}

void			ft_rotate_left(t_rb_tree *father, t_map *map)
{
	t_rb_tree *right_son;

	right_son = father->right;
	father->right = right_son->left;
	if (father->right != map->nil)
		father->right->parent = father;
	right_son->parent = father->parent;
	if (father->parent == 0)
	{
		map->root = right_son;
		map->root->color = RB_BLACK;
	}
	else if (father == father->parent->left)
		father->parent->left = right_son;
	else
		father->parent->right = right_son;
	right_son->left = father;
	father->parent = right_son;
}
