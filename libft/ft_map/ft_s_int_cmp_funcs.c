/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shapka.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggerardy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 17:25:22 by ggerardy          #+#    #+#             */
/*   Updated: 2019/05/19 21:23:40 by ggerardy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_types.h"
#include <unistd.h>

int		ft_cmp_int8(void *a, void *b)
{
	return ((t_int8)a - (t_int8)b);
}

int		ft_cmp_int16(void *a, void *b)
{
	return ((t_int16)a - (t_int16)b);
}

int		ft_cmp_int32(void *a, void *b)
{
	return ((t_int32)a - (t_int32)b);
}

int		ft_cmp_int64(void *a, void *b)
{
	t_int64 l;
	t_int64 r;

	l = (t_int64)a;
	r = (t_int64)b;
	if (l < r)
		return (-1);
	else if (l > r)
		return (1);
	else
		return (0);
}

int		ft_cmp_ssize_t(void *a, void *b)
{
	ssize_t l;
	ssize_t r;

	l = (ssize_t)a;
	r = (ssize_t)b;
	if (l < r)
		return (-1);
	else if (l > r)
		return (1);
	else
		return (0);
}
