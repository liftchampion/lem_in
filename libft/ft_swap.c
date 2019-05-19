/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_swap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggerardy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/02 14:50:09 by ggerardy          #+#    #+#             */
/*   Updated: 2019/03/15 00:55:37 by ggerardy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void		ft_swap(void *a, void *b, size_t s)
{
	unsigned char	tmp;
	size_t			i;

	i = 0;
	while (i < s)
	{
		tmp = *(unsigned char*)a;
		*(unsigned char*)a = *(unsigned char*)b;
		*(unsigned char*)b = tmp;
		++a;
		++b;
		++i;
	}
}
