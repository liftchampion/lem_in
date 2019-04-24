/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggerardy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 09:16:36 by ggerardy          #+#    #+#             */
/*   Updated: 2019/04/19 09:16:36 by ggerardy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "libft.h"

ssize_t		ft_read(int fd, void *buf, size_t buf_size)
{
	size_t	read_size;
	ssize_t	read_size_increment;
	int		hp;

	if (buf_size <= 512)
		return (read(fd, buf, buf_size));
	read_size = 0;
	hp = 1;
	while (read_size < buf_size && hp)
	{
		read_size_increment = read(fd, buf, buf_size - read_size);
		if (read_size_increment == -1)
			return (-1);
		hp -= read_size_increment == 0;
		hp = (read_size_increment > 0) ? 1 : hp;
		read_size += read_size_increment;
	}
	return (read_size);
}
