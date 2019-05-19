/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehugh-be <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/16 22:40:21 by ehugh-be          #+#    #+#             */
/*   Updated: 2019/03/15 00:55:37 by ggerardy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_string_set_value(t_string **str, size_t n, char filler,
																char value)
{
	size_t i;

	if (!str || !*str)
		return (-1);
	i = (*str)->len;
	while (i <= n)
	{
		if (!ft_string_push_back(str, filler))
			return (0);
		++i;
	}
	(*str)->data[n] = value;
	return (1);
}
