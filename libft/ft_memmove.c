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
#include "libft.h"

void		*ft_memmove(void *dest, const void *src, size_t n)
{
	if ((size_t)dest + n < (size_t)src || (size_t)src >= (size_t)dest)
		return (ft_memcpy(dest, src, n));
	while (n > 0)
	{
		((unsigned char*)dest)[n - 1] = ((unsigned char*)src)[n - 1];
		n--;
	}
	return (dest);
}
