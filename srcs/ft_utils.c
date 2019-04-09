/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggerardy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 19:50:42 by ggerardy          #+#    #+#             */
/*   Updated: 2019/04/08 22:10:45 by ggerardy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "len_in.h"
#include "lem_in_structs.h"

int 	ft_free_node(t_node *nd, int ret)
{
	if (!nd)
		return (ret);
	free(nd->name);
	ft_free_vector(&nd->children);
	ft_free_vector(&nd->parents);
	return (ret);
}

int 	ft_free_data(t_data *dt, int ret)
{
	size_t i;

	if (!dt)
		return (ret);
	i = (size_t)-1;
	while (dt->nodes && ++i < dt->nodes->len)
		ft_free_node(dt->nodes->data[i], 0);
	free(dt->nodes);
	ft_free_map(&dt->name_to_idx);
	free(dt);
	free(dt->dsts);
	free(dt->tmp_line);
	return (ret);
}

void		ft_print_parsed(t_data *dt)
{
	ft_printf("Ant-count: %d\n", dt->ant_count);
	for (size_t i = 0; i < dt->nodes->len; ++i)
	{
		ft_printf("%s %d %d idx=%d\n", ((t_node*)dt->nodes->data[i])->name,
								((t_node*)dt->nodes->data[i])->x,
								((t_node*)dt->nodes->data[i])->y,
				(int)*(void**)ft_map_get(dt->name_to_idx, ((t_node*)dt->nodes->data[i])->name));
	}
}



