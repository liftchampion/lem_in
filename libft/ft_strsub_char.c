/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub_char.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggerardy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 20:23:32 by ggerardy          #+#    #+#             */
/*   Updated: 2019/04/08 20:29:10 by ggerardy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char		*ft_strsub_char_m(char **s, char c, int init_size)
{
	char			*str;
	t_string		*res;

	if (!s || !*s)
		return (0);
	if (!(res = ft_make_string(init_size)))
		return (0);
	while (**s != c && **s)
	{
		if (!ft_string_push_back(&res, **s))
			return (0);
		++(*s);
	}
	str = res->data;
	free(res);
	return (str);
}
