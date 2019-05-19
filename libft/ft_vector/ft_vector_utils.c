/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggerardy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 21:08:18 by ggerardy          #+#    #+#             */
/*   Updated: 2019/04/16 21:08:18 by ggerardy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "ft_string.h"

static inline void	ft_free_array(void **arr, size_t size,
		void (*free_data)(void*))
{
	size_t i;

	if (!free_data)
		return ;
	i = (size_t)-1;
	while (++i < size)
	{
		free_data(arr[i]);
	}
}

void				ft_free_vector_simple(void *v_ptr)
{
	t_vector *v;

	v = v_ptr;
	if (!v)
		return ;
	ft_free_array(v->data, v->len, v->free_data);
	free(v->data);
	free(v);
}

void				ft_free_vector(t_vector **v)
{
	if (!v)
		return ;
	ft_free_vector_simple(*v);
	*v = 0;
}

int					ft_free_ret_vector(t_vector **v, int ret)
{
	ft_free_vector(v);
	return (ret);
}

t_int8				ft_vector_fit(t_vector **v_ptr)
{
	t_vector *v;

	if (!v_ptr || !*v_ptr)
		return (-1);
	v = *v_ptr;
	if (v->len == v->capacity - 1)
		return (1);
	v->data = ft_realloc_free(v->data, v->capacity * sizeof(void*),
			(v->len == 0 ? 2 : v->len + 1) * sizeof(void*), v->free_data);
	if (!v->data)
	{
		ft_free_vector(v_ptr);
		return (0);
	}
	v->data[v->len] = 0;
	v->capacity = v->len == 0 ? 2 : v->len + 1;
	return (1);
}
