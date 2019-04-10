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

	if (ft_get_next_line(FD, &ln, READ_BUFF) <= 0)
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

int 	ft_find_in_map(char *ln, t_data *dt)
{
	void	**map_value;

	if (!(map_value = ft_map_get(dt->name_to_idx, ln)) ||
		(*map_value) == dt->name_to_idx->nil)
		return (-1);
	return ((int)(*map_value));
}

int 	ft_add_link(int i1, int i2, t_data *dt)
{
	t_node *n1;
	t_node *n1_;
	t_node *n2;
	t_node *n2_;

	n1 = dt->nodes->data[i1];
	n1_ = dt->nodes->data[i1 + 1];
	n2 = dt->nodes->data[i2];
	n2_ = dt->nodes->data[i2 + 1];
	if (!ft_vector_push_back(&n1->children, TO_EDGE(i2 + 1, 1)) ||
		!ft_vector_push_back(&n1_->parents, TO_EDGE(i2, 1)) ||
		!ft_vector_push_back(&n2->children, TO_EDGE(i1 + 1, 1)) ||
		!ft_vector_push_back(&n2_->parents, TO_EDGE(i1, 1)))
		return (0);
	return (1);
}

int 	ft_parse_link(char *ln, t_data *dt)
{
	char	*f_name;
	char	*s_name;
	int		i1;
	int		i2;

	char *tmp = ln;
	if (*ln == '#')
		return (ft_parse_hash(dt, ln, LINKS));
	if (!(f_name = ft_strsub_char_m(&ln, '-', INIT_NAME_LEN)))
		return (0);
	if (*(ln++) != '-')
	{
		ft_printf("%s\n", tmp);
		return (free_ret(f_name, -1 * (dt->start == dt->end)));
	}
	if (!(s_name = ft_strsub_char_m(&ln, '\0', INIT_NAME_LEN)))
		return (free_ret(f_name, 0));
	if ((i1 = ft_find_in_map(f_name, dt)) < 0 ||
		(i2 = ft_find_in_map(s_name, dt)) < 0)
		return (free_ret(f_name, 0) + free_ret(s_name, -1));
	if (!ft_add_link(i1, i2, dt))
		return (free_ret(f_name, 0) + free_ret(s_name, 0));
	free(s_name);
	free(f_name);
	return (1);
}

int 	ft_parse_links(t_data *dt)
{
	char *ln;
	int parse_res;

	while ((ln = (char*)1lu) && ft_get_next_line(FD, &ln, READ_BUFF))
	{
		if (!ln)
			return (0);
		if ((parse_res = ft_parse_link(ln, dt)) <= 0)
			return (free_ret(ln, parse_res));
		free(ln);
	}
	return (1);
}

int 	ft_check_links_begin(char *end, t_node *nd, t_data *dt)
{
	char *ln;

	ln = end - 1 - ft_strlen(nd->name);
	ft_free_node(nd, 0);
	if (ft_strchr(ln, '-'))
		return (ft_parse_link(ln, dt) * -2);
	return (-1 * (dt->start == dt->end));
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

int 	ft_check_start_end(t_data *dt)
{
	if (dt->start == -1 || dt->end == -1 ||
		dt->start >= (int)dt->nodes->len || dt->end >= (int)dt->nodes->len)
		return (0);
	return (1);
}

t_data	*ft_parser(void)
{
	t_data		*dt;
	int 		parse_res;

	if (!(dt = ft_make_data()))
		return (0);
	if ((dt->ant_count = ft_parse_ants_count()) <= 0)
		return ((void*)(size_t)ft_free_data(dt, 0));
	if (!(parse_res = ft_parse_rooms(dt)))
		return ((void*)(size_t)ft_free_data(dt, 0));
	if (!ft_check_start_end(dt))
		return ((void*)(size_t)ft_free_data(dt, 0));
	if (parse_res == -1)
		return (dt);
	if (!ft_parse_links(dt))
		return ((void*)(size_t)ft_free_data(dt, 0));
	if (!(dt->heap = make_heap(dt->nodes->len)) ||
		!(dt->dsts = malloc(sizeof(int) * dt->nodes->len)))
		return ((void*)(size_t)ft_free_data(dt, 0));
	return (dt);
}











