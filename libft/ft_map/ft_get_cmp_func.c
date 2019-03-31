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

t_cmp_func		ft_get_int_cmp_func(t_type type)
{
	if (type == INT8_T)
		return (ft_cmp_int8);
	else if (type == UINT8_T)
		return (ft_cmp_uint8);
	else if (type == INT16_T)
		return (ft_cmp_int16);
	else if (type == UINT16_T)
		return (ft_cmp_uint16);
	else if (type == INT32_T)
		return (ft_cmp_int32);
	else if (type == UINT32_T)
		return (ft_cmp_uint32);
	else if (type == INT64_T)
		return (ft_cmp_int64);
	else if (type == UINT64_T)
		return (ft_cmp_uint64);
	else if (type == SSIZE_T)
		return (ft_cmp_ssize_t);
	else if (type == SIZE_T)
		return (ft_cmp_size_t);
	return (0);
}

t_cmp_func		ft_get_char_cmp_func(t_type type)
{
	if (type == CHAR)
		return (ft_cmp_char);
	else if (type == STRING)
		return (ft_cmp_str);
	return (0);
}

t_cmp_func		ft_get_cmp_func(t_type type)
{
	if (type >= INT8_T && type <= SSIZE_T)
		return (ft_get_int_cmp_func(type));
	else if (type >= CHAR && type <= STRING)
		return (ft_get_char_cmp_func(type));
	return (0);
}
