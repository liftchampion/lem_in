/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matrix_trans.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgalyeon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 12:03:24 by rgalyeon          #+#    #+#             */
/*   Updated: 2019/03/15 00:55:37 by ggerardy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix_ft.h"

t_matrix	*ft_matrix_trans(t_matrix *a)
{
	t_matrix	*tp;
	size_t		i;
	size_t		j;

	if (!a || !(a->matrix) || a->col == 0 || a->row == 0)
		return (NULL);
	if (!(tp = ft_matrix_create(a->col, a->row)))
		return (NULL);
	i = -1;
	while (++i < a->row)
	{
		j = -1;
		while (++j < a->col)
			(tp->matrix)[j][i] = (a->matrix)[i][j];
	}
	tp->row = a->col;
	tp->col = a->row;
	return (tp);
}
