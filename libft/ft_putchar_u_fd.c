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

void			ft_putchar_u_fd(int c, int fd)
{
	char uni_char[5];

	ft_bzero(uni_char, 5);
	if (c >= 0 && c <= ft_pow(2, 21) - 1)
	{
		ft_int_to_unicode(c, uni_char);
	}
	else
	{
		uni_char[0] = (char)c;
	}
	write(fd, uni_char, ft_strlen(uni_char));
}
