/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matrix_create.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgalyeon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 04:54:37 by rgalyeon          #+#    #+#             */
/*   Updated: 2019/03/15 00:55:37 by ggerardy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix_ft.h"

static t_matrix	*ft_norminette(t_matrix **mass, size_t n, size_t m)
{
	size_t	i;
	size_t	j;

	i = -1;
	while (++i < m)
	{
		((*mass)->matrix)[i] = (double *)ft_memalloc(sizeof(double) * n);
		if (!(((*mass)->matrix)[i]))
		{
			j = -1;
			while (++j < i)
				free(((*mass)->matrix)[j]);
			free((*mass)->matrix);
			free(*mass);
			return (NULL);
		}
	}
	(*mass)->row = m;
	(*mass)->col = n;
	return (*mass);
}

t_matrix		*ft_matrix_create(size_t m, size_t n)
{
	t_matrix	*mass;

	if (m == 0 || n == 0)
		return (NULL);
	if (!(mass = (t_matrix *)ft_memalloc(sizeof(t_matrix))))
		return (NULL);
	mass->matrix = (double **)ft_memalloc(sizeof(double *) * m);
	if (!(mass->matrix))
	{
		free(mass);
		return (NULL);
	}
	mass = ft_norminette(&mass, n, m);
	if (!mass)
		return (NULL);
	return (mass);
}
