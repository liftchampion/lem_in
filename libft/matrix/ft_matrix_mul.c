/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matrix_mul.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgalyeon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 05:48:39 by rgalyeon          #+#    #+#             */
/*   Updated: 2019/03/15 00:55:37 by ggerardy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix_ft.h"

static t_matrix	*ft_costil2(t_matrix **new, t_matrix **a, t_matrix **b)
{
	size_t	i;
	size_t	j;
	size_t	k;

	i = 0;
	j = 0;
	while (i < (*a)->row)
	{
		j = -1;
		while (++j < (*b)->col)
		{
			((*new)->matrix)[i][j] = 0;
			k = 0;
			while (k < (*a)->col)
			{
				((*new)->matrix)[i][j] += ((*a)->matrix)[i][k] *
					((*b)->matrix)[k][j];
				k++;
			}
		}
		i++;
	}
	(*new)->row = i;
	(*new)->col = j;
	return (*new);
}

t_matrix		*ft_matrix_mul(t_matrix *a, t_matrix *b)
{
	t_matrix	*new;

	if ((!a) || (!b) || (!(a->matrix)) || (!(b->matrix)) ||
			(a->col != b->row) || (a->col == 0) || (a->row == 0) ||
			(b->col == 0) || (b->row == 0) ||
			(!(a->matrix)) || (!(b->matrix)))
		return (NULL);
	if (!(new = ft_matrix_create(a->row, b->col)))
		return (NULL);
	new = ft_costil2(&new, &a, &b);
	return (new);
}
