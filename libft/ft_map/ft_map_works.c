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
#include "ft_types.h"

void			**ft_map_get(t_map *map, void *key)
{
	return (rb_tree_insert_data(map, key));
}

void			ft_map_del(t_map *map, void *key)
{
	rb_tree_delete_key(map, key);
}

t_map			*ft_make_std_map(t_type key_type, t_type value_type)
{
	t_map_info	*info;
	t_map		*map;
	t_rb_tree	*nil;

	info = (t_map_info*)malloc(sizeof(t_map_info));
	if (!info)
		return (0);
	*info = (t_map_info){key_type, value_type, ft_get_cmp_func(key_type),
					ft_get_del_func(key_type), ft_get_del_func(value_type)};
	nil = (t_rb_tree*)malloc(sizeof(t_rb_tree));
	if (!nil)
		return (0);
	*nil = (t_rb_tree){0, 0, 0, RB_BLACK, 0, 0};
	map = (t_map*)malloc(sizeof(t_map));
	if (!map)
		return (0);
	*map = (t_map){0, info, 0, nil};
	return (map);
}

t_map			*ft_make_custom_value_map(t_type key_type,
							t_del_func del_value_func)
{
	t_map_info	*info;
	t_map		*map;
	t_rb_tree	*nil;

	info = (t_map_info*)malloc(sizeof(t_map_info));
	if (!info)
		return (0);
	*info = (t_map_info){key_type, CUSTOM, ft_get_cmp_func(key_type),
								ft_get_del_func(key_type), del_value_func};
	nil = (t_rb_tree*)malloc(sizeof(t_rb_tree));
	if (!nil)
		return (0);
	*nil = (t_rb_tree){0, 0, 0, RB_BLACK, 0, 0};
	map = (t_map*)malloc(sizeof(t_map));
	if (!map)
		return (0);
	*map = (t_map){0, info, 0, nil};
	return (map);
}

void			ft_free_map(t_map **map)
{
	if (!map)
		return ;
	rb_tree_free(&((*map)->root), *map);
	free((*map)->nil);
	free((*map)->info);
	free(*map);
	*map = 0;
}
