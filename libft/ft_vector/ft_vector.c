/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggerardy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/23 11:42:40 by ggerardy          #+#    #+#             */
/*   Updated: 2019/03/15 00:55:37 by ggerardy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "ft_string.h"

t_vector		*ft_make_vector(size_t init_size)
{
	t_vector *v;

	v = (t_vector*)ft_memalloc(sizeof(t_vector) * 1);
	if (!v)
		return (0);
	v->capacity = init_size <= 1 ? 2 : init_size;
	v->data = (void**)malloc(sizeof(void*) * (v->capacity));
	if (!v->data)
	{
		free(v);
		return (0);
	}
	v->data[0] = 0;
	return (v);
}

t_vector		*ft_make_vector_free(size_t init_size, void (*free_data)(void*))
{
	t_vector *v;

	if (!(v = ft_make_vector(init_size)))
		return (0);
	v->free_data = free_data;
	return (v);
}

t_int8			ft_vector_push_back(t_vector **v_ptr, void *c)
{
	t_vector *v;

	if (!v_ptr || !*v_ptr)
		return (-1);
	v = *v_ptr;
	if (v->len == v->capacity - 1)
	{
		v->data = ft_realloc_free(v->data, v->capacity * sizeof(void*),
				v->capacity * 2 * sizeof(void*), (*v_ptr)->free_data);
		if (!v->data)
		{
			ft_free_vector(v_ptr);
			return (0);
		}
		v->capacity *= 2;
	}
	v->data[v->len++] = c;
	v->data[v->len] = 0;
	return (1);
}
