/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggerardy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 18:37:52 by ggerardy          #+#    #+#             */
/*   Updated: 2019/04/09 18:21:08 by ggerardy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "len_in.h"

int			ft_parse_ants_count(void)
{
	char *ln;
	int count;

	if (ft_get_next_line(0, &ln, READ_BUFF) <= 0)
		return (0);
	if ((count = ft_atoi(ln)) <= 0)
		return (free_ret(ln, 0));
	if (ln[ft_intlen(count)])
		return (free_ret(ln, 0));
	return (free_ret(ln, count));
}

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
		return (0);
	if (!(map_value = ft_map_get(dt->name_to_idx, node->name)) ||
		(*map_value) != dt->name_to_idx->nil)
		return (0);
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

int		ft_parse_hash(t_data *dt, char *ln, t_parse_mode pm)
{
	if (ln[1] != '#' || pm == LINKS)
		return (1);
	if (!ft_strcmp("start", ln + 2))
	{
		if (dt->start != -1)
			return (0);
		dt->start = dt->nodes->len;
	}
	if (!ft_strcmp("end", ln + 2))
	{
		if (dt->end != -1)
			return (0);
		dt->end = dt->nodes->len;
	}
	return (1);
}

int		ft_parse_room(char *ln, t_data *dt)
{
	t_node *node;
	void **map_value;

	if (*ln == '#')
		return (ft_parse_hash(dt, ln, NODES));
	if (!(node = ft_make_node()))
		return (0);
	if (!(node->name = ft_strsub_char_m(&ln, ' ', 16)))
		return (0);
	if (!(map_value = ft_map_get(dt->name_to_idx, node->name)) ||
		(*map_value) != dt->name_to_idx->nil)
		return (0);
	(*map_value) = (void*)dt->nodes->len;
	if (*(ln++) != ' ')
		return (0);
	node->x = ft_atoi_m(&ln);
	if (*(ln++) != ' ')
		return (0);
	node->y = ft_atoi_m(&ln);
	if (*ln)
		return (0);
	if (!(ft_vector_push_back(&dt->nodes, node)))
		return (0);
	return (ft_split_room(dt));
}

int		ft_parse_rooms(t_data *dt)
{
	char *ln;

	while ((ln = (char*)1lu) && ft_get_next_line(0, &ln, READ_BUFF))
	{
		if (!ln)
			return (0);
		if (!ft_parse_room(ln, dt))
			return (free_ret(ln, 0));
		free(ln);
	}
	return (1);
}

t_vector	*ft_parser(void)
{
	t_data		*dt;

	if (!(dt = ft_make_data()))
		return (0);
	if ((dt->ant_count = ft_parse_ants_count()) <= 0)
		return ((void*)(size_t)ft_free_data(dt, 0));
	if (!ft_parse_rooms(dt))
		return ((void*)(size_t)ft_free_data(dt, 0));
	ft_print_parsed(dt);
	return (0);
}











