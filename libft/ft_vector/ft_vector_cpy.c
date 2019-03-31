/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector_cpy.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggerardy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 05:33:12 by ggerardy          #+#    #+#             */
/*   Updated: 2019/03/15 00:55:37 by ggerardy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_vector		*ft_vector_cpy(const t_vector *src)
{
	t_vector *v;

	if (!src)
		return (0);
	if (!(v = ft_make_vector(src->capacity)) || !ft_memcpy(v->data, src->data,
			sizeof(void*) * src->capacity))
		return (0);
	v->capacity = src->capacity;
	v->len = src->len;
	v->offset = src->offset;
	return (v);
}
