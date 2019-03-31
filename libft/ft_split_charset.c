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

static unsigned int	ft_count_words(char const *str, char const *charset)
{
	int c;
	int was_space;

	c = 0;
	was_space = 1;
	while (*str && ft_is_in_charset(*str, charset))
	{
		str++;
	}
	while (*str)
	{
		if (!ft_is_in_charset(*str, charset) && was_space)
			c++;
		was_space = ft_is_in_charset(*str, charset);
		str++;
	}
	return (c);
}

static unsigned int	ft_strlen_delim(char const *str, int delim_by_spaces,
									char const *charset)
{
	unsigned int len;

	len = 0;
	while (*str && (!delim_by_spaces || !ft_is_in_charset(*str, charset)))
	{
		len++;
		str++;
	}
	return (len);
}

static unsigned int	ft_strlcpy_delim(char *dest, char const *src,
		unsigned int size, char const *c)
{
	unsigned int i;

	i = 0;
	while (src[i] != '\0' && i < size - 1 && !ft_is_in_charset(*src, c))
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (ft_strlen_delim(src, 0, c));
}

static int			ft_initializator(char ***strs, int count_words,
		int *was_space, unsigned int *i)
{
	*was_space = 1;
	*i = 0;
	*strs = (char**)malloc(sizeof(char*) * count_words + 1);
	if (!*strs)
		return (0);
	strs[0][0] = 0;
	return (1);
}

char				**ft_split_charset(char const *str, char const *c)
{
	char			**strs;
	int				was_space;
	unsigned int	i;

	if (!ft_initializator(&strs, ft_count_words(str, c), &was_space, &i))
		return (0);
	while (*str)
	{
		if (was_space && !ft_is_in_charset(*str, c))
		{
			strs[i] = (char*)malloc(sizeof(char) *
					ft_strlen_delim(str, 1, c) + 1);
			strs[i + 1] = 0;
			if (!strs[i])
			{
				ft_free_matrix((void**)strs, -1);
				return (0);
			}
			ft_strlcpy_delim(strs[i++], str, ft_strlen_delim(str, 1, c) + 1, c);
		}
		was_space = ft_is_in_charset(*str, c);
		str++;
	}
	return (strs);
}
