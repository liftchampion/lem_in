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

char		*ft_strstr(const char *str, const char *to_find)
{
	char *a;
	char *b;

	b = (char*)to_find;
	if (*b == 0)
		return ((char*)str);
	while (*str != '\0')
	{
		str++;
		if (*(str - 1) != *b)
			continue;
		a = (char*)str - 1;
		while (1)
		{
			if (*b == 0)
				return ((char*)str - 1);
			if (*a++ != *b++)
				break ;
		}
		b = (char*)to_find;
	}
	return (0);
}
