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

int				ft_atoi(const char *str)
{
	int				sign;
	int				i;
	long long int	res;
	long long int	res_tmp;

	i = 0;
	res = 0;
	while (*str && ft_isspace(*str))
		str++;
	sign = (*str == '-') ? -1 : 1;
	if (*str == '+' || *str == '-')
		str++;
	while (*str && ft_isdigit(*str))
	{
		res_tmp = res;
		res = res * 10 + (*str++ - '0') * sign;
		if ((res < res_tmp && sign == 1) || (res > res_tmp && sign == -1))
			return (sign == 1 ? -1 : 0);
	}
	return ((int)res);
}
