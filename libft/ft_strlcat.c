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

#include <stdlib.h>
#include "libft.h"

size_t		ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t i;
	size_t dest_len;
	size_t src_len;

	i = 0;
	src_len = ft_strlen(src);
	while (*dest && i < size)
	{
		i++;
		dest++;
	}
	dest_len = i;
	if (size != 0)
		while (*src && i < size - 1)
		{
			i++;
			*dest = *src;
			src++;
			dest++;
		}
	if (i < size)
		*dest = '\0';
	return (dest_len + src_len);
}
