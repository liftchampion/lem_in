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

int		ft_atoi_m(char **str)
{
	int sign;
	int res;

	res = 0;
	if (!str || !*str)
		return (0);
	while (**str && ft_isspace(**str))
		(*str)++;
	sign = (**str == '-') ? -1 : 1;
	if (**str == '+' || **str == '-')
		(*str)++;
	while (**str && ft_isdigit(**str))
	{
		res = res * 10 + (*(*str)++ - '0') * sign;
	}
	return (res);
}

long	ft_atoi_base_m(const char **str, int radix)
{
	static char	base[] = "0123456789abcdef";
	long		sign;
	long		res;

	res = 0;
	if (!str || !*str || !(radix >= 1 && radix <= 16))
		return (0);
	while (**str && ft_isspace(**str))
		(*str)++;
	sign = (**str == '-') ? -1 : 1;
	if (**str == '+' || **str == '-')
		(*str)++;
	while (**str && ft_strchr(base, **str))
	{
		res = res * radix + (ft_strchr(base,
				ft_tolower(*(*str)++)) - base) * sign;
	}
	return (res);
}
