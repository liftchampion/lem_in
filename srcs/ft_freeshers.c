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

int 	ft_free_node(t_node *nd, int ret)
{
	if (!nd)
		return (ret);
	free(nd->name);
	ft_free_vector(&nd->chs);
	free(nd);
	return (ret);
}

int 	ft_free_data(t_data *dt, int ret)
{
	size_t i;

	ft_get_next_line(0, 0, 0);
	if (!dt)
		return (ret);
	i = (size_t)-1;
	while (dt->nodes && ++i < dt->nodes->len)
		ft_free_node(dt->nodes->data[i], 0);
	free(dt->nodes->data);
	free(dt->nodes);
	ft_free_vector(&dt->path);
	ft_free_heap(dt->heap, 0);
	ft_free_map(&dt->name_to_idx);
	ft_free_vector(&dt->flows);
	free(dt->dsts);
	free(dt->tmp_line);
	free(dt);
	return (ret);
}

int 	ft_free_heap(t_heap *hp, int ret)
{
	if (!hp)
		return (ret);
	free(hp->name);
	free(hp->num);
	free(hp->weight);
	free(hp);
	return (ret);
}
