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

#include <string.h>

void		*ft_memchr(const void *str, int ch, size_t n)
{
	unsigned char	c;
	size_t			i;

	c = (unsigned char)ch;
	i = 0;
	while (i < n)
	{
		if (*(unsigned char*)str == c)
		{
			return ((void*)str);
		}
		i++;
		str++;
	}
	if (n > 0 && *(char*)(str - 1) == 0 && c == 0)
		return ((void*)(str - 1));
	return (0);
}
