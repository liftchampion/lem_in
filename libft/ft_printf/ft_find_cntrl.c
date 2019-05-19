/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_find_cntrl.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehugh-be <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/18 14:03:08 by ehugh-be          #+#    #+#             */
/*   Updated: 2019/03/15 00:55:37 by ggerardy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_utils.h"

int	ft_find_cntrl(const char **frmt, t_string **str)
{
	char slash;

	if (!str || !*str)
		return (0);
	slash = 0;
	while (**frmt && **frmt != '%' && !(**frmt == CLR_CNTRL && !slash && CLR))
	{
		slash = (**frmt == '\\') ? (char)1 : (char)0;
		if (!ft_string_push_back(str, **frmt))
			return (0);
		(*frmt)++;
	}
	if (**frmt)
		(*frmt)++;
	return (1);
}
