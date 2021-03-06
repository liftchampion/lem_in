/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_freeshers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggerardy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 10:39:38 by ggerardy          #+#    #+#             */
/*   Updated: 2019/04/10 10:39:38 by ggerardy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "len_in.h"

int		ft_free_node(t_node *nd, int ret)
{
	if (!nd)
		return (ret);
	free(nd->name);
	ft_free_vector(&nd->chs);
	free(nd);
	return (ret);
}

int		ft_free_for_mlx(void *ptr)
{
	t_data *dt;

	dt = ptr;
	return (ft_free_data(dt, 0));
}

int		ft_free_data(t_data *dt, int ret)
{
	size_t i;

	ft_get_next_line(0, 0, 0);
	if (!(i = (size_t)-1) || !dt)
		return (ret);
	while (dt->nodes && ++i < dt->nodes->len)
		ft_free_node(dt->nodes->data[i], 0);
	free(dt->nodes->data);
	free(dt->nodes);
	ft_free_vector(&dt->path);
	ft_free_heap(dt->heap, 0);
	ft_free_map(&dt->name_to_idx);
	ft_free_vector(&dt->flows);
	ft_free_string(&dt->output);
	ft_free_vector(&dt->ant_names);
	free(dt->dsts);
	free(dt->ants);
	free(dt->gone_ants);
	free(dt->wave_sizes);
	free(dt->prs);
	free(dt->sorted_nodes);
	free(dt->name_to_pos);
	free(dt->dims);
	free(dt);
	return (ret);
}

int		ft_free_heap(t_heap *hp, int ret)
{
	if (!hp)
		return (ret);
	free(hp->name);
	free(hp->num);
	free(hp->weight);
	free(hp);
	return (ret);
}
