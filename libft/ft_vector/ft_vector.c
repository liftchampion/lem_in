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

	v = (t_vector*)malloc(sizeof(t_vector) * 1);
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
	v->len = 0;
	v->offset = 0;
	return (v);
}

void			ft_free_vector(t_vector **v)
{
	if (!v || !*v)
		return ;
	free((*v)->data);
	free(*v);
	*v = 0;
}

t_int8			ft_vector_push_back(t_vector **v_ptr, void *c)
{
	t_vector *v;

	if (!v_ptr || !*v_ptr)
		return (-1);
	v = *v_ptr;
	if (v->len == v->capacity - 1)
	{
		v->data = ft_realloc(v->data, v->capacity * sizeof(void*),
				v->capacity * 2 * sizeof(void*));
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

t_int8			ft_vector_fit(t_vector **v_ptr)
{
	t_vector *v;

	if (!v_ptr || !*v_ptr)
		return (-1);
	v = *v_ptr;
	if (v->len == v->capacity - 1)
		return (1);
	v->data = ft_realloc(v->data, v->capacity * sizeof(void*),
			(v->len == 0 ? 2 : v->len + 1) * sizeof(void*));
	if (!v->data)
	{
		ft_free_vector(v_ptr);
		return (0);
	}
	v->data[v->len] = 0;
	v->capacity = v->len == 0 ? 2 : v->len + 1;
	return (1);
}
