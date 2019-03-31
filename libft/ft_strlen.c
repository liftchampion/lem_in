/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehugh-be <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 15:46:57 by ehugh-be          #+#    #+#             */
/*   Updated: 2019/03/15 00:55:37 by ggerardy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	ft_unilen(int u)
{
	if (u < 128)
		return (1);
	else if (u < 2048)
		return (2);
	else if (u < 65536)
		return (3);
	else
		return (4);
}

size_t	ft_strlen_u(const int *s, char f)
{
	size_t len;

	len = 0;
	if (f)
		return (ft_strlen((char*)s));
	while (*s)
	{
		if (*s < 128)
			len++;
		else if (*s < 2048)
			len += 2;
		else if (*s < 65536)
			len += 3;
		else
			len += 4;
		s++;
	}
	return (len);
}

size_t	ft_strlen(const char *s)
{
	size_t len;

	len = 0;
	if (!s)
		return (0);
	while (s[len])
		len++;
	return (len);
}
