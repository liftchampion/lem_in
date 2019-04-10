/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser_rooms.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggerardy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 11:02:33 by ggerardy          #+#    #+#             */
/*   Updated: 2019/04/10 11:02:33 by ggerardy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "len_in.h"

int		ft_split_room(t_data *dt)
{
	t_node	*node;
	void	**map_value;
	t_node	*old_node;
	int 	node_idx;

	node_idx = dt->nodes->len;
	old_node = dt->nodes->data[node_idx - 1];
	if (!(node = ft_make_node()))
		return (0);
	if (!(node->name = ft_strjoin(old_node->name, NODE_POSTFIX)))
		return (ft_free_node(node, 0));
	if (!(map_value = ft_map_get(dt->name_to_idx, node->name)) ||
			(*map_value) != dt->name_to_idx->nil)
		return (ft_free_node(node, 0));
	(*map_value) = (void*)(size_t)node_idx;
	node->x = old_node->x;
	node->y = old_node->y;
	if (!ft_vector_push_back(&dt->nodes, node) ||
			!ft_vector_push_back(&node->children, TO_EDGE(node_idx - 1, 1)) ||
			!ft_vector_push_back(&node->parents, TO_EDGE(node_idx - 1, 1)) ||
			!ft_vector_push_back(&old_node->children, TO_EDGE(node_idx, 1)) ||
			!ft_vector_push_back(&old_node->parents, TO_EDGE(node_idx, 1)))
		return (0);
	return (1);
}

int		ft_parse_room(char *ln, t_data *dt)
{
	t_node *node;
	void **map_value;

	if (*ln == '#' || *ln == 'L')
		return (*ln == '#' ? ft_parse_hash(dt, ln, NODES) : -1);
	if (!(node = ft_make_node()))
		return (0);
	if (!(node->name = ft_strsub_char_m(&ln, ' ', INIT_NAME_LEN)))
		return (ft_free_node(node, 0));
	if (*(ln++) != ' ')
		return (ft_check_links_begin(ln, node, dt));
	node->x = ft_atoi_m(&ln);
	if (*(ln++) != ' ')
		return (ft_free_node(node, -1 * (dt->start == dt->end)));
	node->y = ft_atoi_m(&ln);
	if (*ln)
		return (ft_free_node(node, -1 * (dt->start == dt->end)));
	if (!(map_value = ft_map_get(dt->name_to_idx, node->name)) ||
			(*map_value) != dt->name_to_idx->nil)
		return (ft_free_node(node, 0));
	(*map_value) = (void*)dt->nodes->len;
	if (!(ft_vector_push_back(&dt->nodes, node)))
		return (ft_free_node(node, 0));
	return (ft_split_room(dt));
}

int		ft_parse_rooms(t_data *dt)
{
	char *ln;
	int parse_res;

	while ((ln = (char*)1lu) && ft_get_next_line(FD, &ln, READ_BUFF))
	{
		if (!ln)
			return (0);
		if ((parse_res = ft_parse_room(ln, dt)) <= 0)
			return (free_ret(ln, parse_res));
		free(ln);
	}
	return (1);
}
