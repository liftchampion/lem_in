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

#ifndef FT_MAP_H
# define FT_MAP_H

# include <stdlib.h>
# include "libft.h"
# include "ft_types.h"

typedef char			t_color;

# define RB_BLACK 'B'
# define RB_RED 'R'

typedef struct			s_rb_tree
{
	struct s_rb_tree	*left;
	struct s_rb_tree	*right;
	struct s_rb_tree	*parent;
	t_color				color;
	void				*key;
	void				*value;
}						t_rb_tree;

typedef struct			s_map_info
{
	t_type				key_type;
	t_type				value_type;
	int					(*cmp_f)(void*, void*);
	void				(*free_key_f)(void*);
	void				(*free_value_f)(void*);
}						t_map_info;

typedef struct			s_map
{
	t_rb_tree			*root;
	t_map_info			*info;
	size_t				size;
	t_rb_tree			*nil;
}						t_map;

typedef struct			s_pair
{
	void*				first;
	void*				second;
}						t_pair;

typedef enum
{
	GOOD,
	REPAINT,
	ROT_LL,
	ROT_LR,
	ROT_RL,
	ROT_RR
}	t_case;

typedef struct			s_relatives
{
	t_rb_tree			*uncle;
	t_rb_tree			*father;
	t_rb_tree			*grandfather;
}						t_relatives;

t_map					*ft_make_std_map(t_type key_type, t_type value_type);
t_map					*ft_make_custom_value_map(t_type key_type,
													t_del_func del_value_func);
void					ft_free_map(t_map **map);
void					**ft_map_get(t_map *map, void *key);
void					ft_map_del(t_map *map, void *key);

void					ft_rotate_left(t_rb_tree *father, t_map *map);
void					ft_rotate_right(t_rb_tree *father, t_map *map);
int						rb_tree_swap_colors(t_rb_tree *node, t_case tree_case);
t_rb_tree				*ft_repaint(t_rb_tree *node);
t_relatives				ft_get_relatives(t_rb_tree *root);
void					rb_tree_balance_delete_helper_right(t_rb_tree **node,
												t_rb_tree *brother, t_map *map);
void					rb_tree_balance_delete_helper_left(t_rb_tree **node,
												t_rb_tree *brother, t_map *map);
t_color					rb_tree_delete_this_node(t_rb_tree *node, t_map *map,
										t_rb_tree *next, t_pair *data_to_free);
t_rb_tree				*rb_tree_find_max(t_rb_tree *node, t_rb_tree *nil);
t_rb_tree				*rb_tree_find_min(t_rb_tree *node, t_rb_tree *nil);
void					rb_tree_free(t_rb_tree **tree, t_map *map);
void					rb_tree_free_node(t_rb_tree *node, t_map *map);

void					**rb_tree_insert_data(t_map *map, void *key);
void					rb_tree_delete_key(t_map *map, void *key);

void					rb_tree_merge(t_map *map1, t_rb_tree **tree2,
												t_map *map2, char free_second);

#endif
