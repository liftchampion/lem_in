/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shapka.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggerardy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/14 21:31:45 by ggerardy          #+#    #+#             */
/*   Updated: 2019/03/15 00:55:37 by ggerardy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_word_count(const char *str)
{
	int count;
	int was_space;

	if (!str)
		return (0);
	count = 0;
	was_space = 1;
	while (*str)
	{
		if (was_space && !ft_isspace(*str))
			count++;
		was_space = ft_isspace(*str) ? 1 : 0;
		str++;
	}
	return (count);
}
