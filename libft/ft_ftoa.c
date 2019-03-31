/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ftoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgalyeon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/02 01:44:23 by rgalyeon          #+#    #+#             */
/*   Updated: 2019/03/15 00:55:37 by ggerardy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

char	*ft_ftoa(double num, int acc)
{
	int		inum;
	double	fnum;
	char	*s;
	char	*s1;
	char	*s2;

	inum = (int)num;
	s = ft_itoa(inum);
	fnum = num - inum;
	if (fnum < 0)
		fnum *= -1;
	fnum = fnum * ft_pow(10, acc);
	s1 = ft_itoa((int)fnum);
	s2 = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s) + 2));
	if (!s2)
		return (NULL);
	inum = 0;
	while (*s)
		s2[inum++] = *s++;
	s2[inum++] = '.';
	while (*s1)
		s2[inum++] = *s1++;
	s2[inum] = '\0';
	return (s2);
}
