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

#include "ft_types.h"

int		ft_cmp_uint8(void *a, void *b)
{
	return ((t_uint8)a - (t_uint8)b);
}

int		ft_cmp_uint16(void *a, void *b)
{
	return ((t_uint16)a - (t_uint16)b);
}

int		ft_cmp_uint32(void *a, void *b)
{
	return ((t_uint32)a - (t_uint32)b);
}

int		ft_cmp_uint64(void *a, void *b)
{
	t_uint64 l;
	t_uint64 r;

	l = (t_uint64)a;
	r = (t_uint64)b;
	if (l < r)
		return (-1);
	else if (l > r)
		return (1);
	else
		return (0);
}

int		ft_cmp_size_t(void *a, void *b)
{
	size_t l;
	size_t r;

	l = (size_t)a;
	r = (size_t)b;
	if (l < r)
		return (-1);
	else if (l > r)
		return (1);
	else
		return (0);
}
