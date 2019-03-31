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

#include "libft.h"

char		*ft_strtrim(char const *s)
{
	size_t space_count_end;
	size_t space_count_begin;
	size_t len;
	size_t i;

	if (!s)
		return (0);
	len = ft_strlen(s);
	i = len;
	space_count_begin = 0;
	space_count_end = 0;
	while (i > 0 && ft_isspace(s[--i]))
		space_count_end++;
	while (s[space_count_begin] && ft_isspace(s[space_count_begin]))
		space_count_begin++;
	return (ft_strsub(s, space_count_begin,
			len - space_count_begin - space_count_end));
}
