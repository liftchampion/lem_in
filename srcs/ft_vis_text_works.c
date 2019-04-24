/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vis_text_works.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggerardy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 10:58:25 by ggerardy          #+#    #+#             */
/*   Updated: 2019/04/24 10:58:25 by ggerardy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "len_in.h"

static inline int	ft_find_longest_word_node(t_data *dt)
{
	t_node	**nodes;
	int		len;
	int		i;
	int		max_len;
	int		curr_len;

	max_len = -1;
	i = -1;
	len = dt->nodes->len;
	nodes = (t_node**)dt->nodes->data;
	while (++i < len)
	{
		curr_len = ft_strlen(nodes[i]->name);
		if (curr_len > max_len)
			max_len = curr_len;
	}
	return (max_len);
}

static inline int	ft_find_longest_word_ant(t_data *dt)
{
	char	**names;
	int		len;
	int		i;
	int		max_len;
	int		curr_len;

	if (!dt->prs->ant_names)
		return (ft_intlen(dt->ant_count));
	max_len = -1;
	i = -1;
	len = dt->ant_names->len;
	names = (char**)dt->ant_names->data;
	while (++i < len)
	{
		curr_len = ft_strlen(names[i]);
		if (curr_len > max_len)
			max_len = curr_len;
	}
	return (max_len);
}

int					ft_check_text_nodes(t_data *dt)
{
	const int	max_word_len = ft_find_longest_word_node(dt);
	t_vis_dims	*ds;
	t_vis_dims	*tmp;

	if (dt->dims->side < max_word_len * 5)
		return (-1);
	if (!(ds = ft_memalloc(sizeof(t_vis_dims))))
		return (0);
	ft_memcpy(ds, dt->dims, sizeof(t_vis_dims));
	while (ds->side)
	{
		if (dt->ant_count * ds->lines_count * ds->side +
				TEXT_H * ds->lines_count < ds->height
				&& (ds->gap > 0 || ds->lines_count == 1))
			break ;
		--ds->side;
		if (ds->side)
			ft_set_dims(dt, ds);
	}
	if (ds->side < max_word_len * 5)
		return (-1);
	ds->use_text_nodes = 1;
	tmp = dt->dims;
	dt->dims = ds;
	return (free_ret(tmp, 1));
}

int					ft_check_text_ants(t_data *dt)
{
	t_vis_dims	*ds;
	t_vis_dims	*tmp;

	dt->dims->longest_ant_name = ft_find_longest_word_ant(dt);
	if (dt->dims->side < 10)
		return (-1);
	if (!(ds = ft_memalloc(sizeof(t_vis_dims))))
		return (0);
	ft_memcpy(ds, dt->dims, sizeof(t_vis_dims));
	while (ds->side)
	{
		if (ds->width -
	(dt->real_nodes_count < ds->line_len ? dt->real_nodes_count : ds->line_len)
				* ds->side > ds->longest_ant_name * 10 * 2 && (ds->gap > 0 ||
				ds->lines_count == 1))
			break ;
		if (--ds->side)
			ft_set_dims(dt, ds);
	}
	if (ds->side < 10)
		return (-1);
	ds->use_text_ants = 1;
	tmp = dt->dims;
	dt->dims = ds;
	return (free_ret(tmp, 1));
}
