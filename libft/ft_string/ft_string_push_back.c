/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_string_push_back.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehugh-be <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/23 15:11:01 by ehugh-be          #+#    #+#             */
/*   Updated: 2019/03/15 00:55:37 by ggerardy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_string_push_back(t_string **str_ptr, char c)
{
	t_string *str;

	if (!str_ptr || !*str_ptr)
		return (-1);
	str = *str_ptr;
	if (str->len == str->capacity - 1)
	{
		str->data = ft_realloc(str->data, str->capacity, str->capacity * 2);
		if (!str->data)
		{
			ft_free_string(str_ptr);
			return (0);
		}
		str->capacity *= 2;
	}
	str->data[str->len++] = c;
	str->data[str->len] = 0;
	return (1);
}

int		ft_string_push_back_s(t_string **str_ptr, char *str)
{
	int		t;
	size_t	l;

	l = 0;
	if (!str)
		return (-1);
	while (*str)
	{
		if ((t = ft_string_push_back(str_ptr, *str)) == 1)
			str++;
		else
			return (t);
		l++;
	}
	return (l);
}

int		ft_string_push_back_n_s(t_string **str_ptr, char *str, size_t n)
{
	int t;

	if (!str)
		return (-1);
	while (*str && n--)
	{
		if ((t = ft_string_push_back(str_ptr, *str)) == 1)
			str++;
		else
			return (t);
	}
	return (1);
}

int		ft_string_push_back_n_c(t_string **str_ptr, long n, char c)
{
	long i;

	if (!str_ptr || !*str_ptr)
		return (-1);
	i = 0;
	while (i < n)
	{
		if (!ft_string_push_back(str_ptr, c))
			return (0);
		i++;
	}
	return (1);
}
