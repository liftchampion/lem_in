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

void		*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	void			*ptr;
	size_t			i;
	unsigned char	ch;

	i = 0;
	if (n == 0)
		return (0);
	ch = (unsigned char)c;
	ptr = dest;
	while (i < n && *(unsigned char*)src != ch)
	{
		*(unsigned char*)dest = *(unsigned char*)src;
		dest++;
		src++;
		i++;
	}
	if (i != n && *(unsigned char*)src == ch)
		*(unsigned char*)dest = ch;
	return (*(unsigned char*)dest == ch ? dest + 1 : 0);
}
