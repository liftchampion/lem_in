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

void		*ft_memcpy(void *dest, const void *src, size_t n)
{
	void	*ptr;
	size_t	i;

	i = 0;
	ptr = dest;
	while (i < n)
	{
		*(char*)dest = *(char*)src;
		dest++;
		src++;
		i++;
	}
	return (ptr);
}
