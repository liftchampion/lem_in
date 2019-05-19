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

#include <unistd.h>
#include "libft.h"

char		*ft_int_to_unicode(int n, char *bytes)
{
	ft_bzero(bytes, 5);
	if (n < 128)
		bytes[0] = (char)n;
	else if (n < 2048)
	{
		bytes[0] = 192 + n / 64;
		bytes[1] = 128 + n % 64;
	}
	else if (n < 65536)
	{
		bytes[0] = 224 + n / 4096;
		bytes[1] = 128 + (n / 64) % 64;
		bytes[2] = 128 + (n % 64);
	}
	else
	{
		bytes[0] = 240 + n / 262144;
		bytes[1] = 128 + (n / 4096) % 64;
		bytes[2] = 128 + (n / 64) % 64;
		bytes[3] = 128 + n % 64;
	}
	return (bytes);
}
