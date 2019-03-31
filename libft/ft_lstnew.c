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

#include "libft.h"
#include <stdlib.h>

t_list		*ft_lstnew(void const *content, size_t content_size)
{
	t_list *new_ptr;

	new_ptr = (t_list*)malloc(sizeof(t_list));
	if (!new_ptr)
		return (0);
	new_ptr->next = 0;
	if (!content)
	{
		new_ptr->content = 0;
		new_ptr->content_size = 0;
	}
	else
	{
		new_ptr->content = malloc(content_size);
		if (!new_ptr->content)
		{
			free(new_ptr);
			return (0);
		}
		ft_memcpy(new_ptr->content, content, content_size);
		new_ptr->content_size = content_size;
	}
	return (new_ptr);
}
