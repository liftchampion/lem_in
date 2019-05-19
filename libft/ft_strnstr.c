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

char		*ft_strnstr(const char *str, const char *to_find, size_t len)
{
	char	*a;
	char	*b;
	size_t	i;
	size_t	j;

	i = 0;
	b = (char*)to_find;
	if (*b == 0)
		return ((char*)str);
	while (*str != '\0' && i++ < len)
	{
		str++;
		if (*(str - 1) != *b)
			continue;
		a = (char*)str - 1;
		j = i - 1;
		while (i++ - 1 < len + 1)
			if (*b == 0)
				return ((char*)str - 1);
			else if (*a++ != *b++)
				break ;
		i = j;
		b = (char*)to_find;
	}
	return (0);
}
