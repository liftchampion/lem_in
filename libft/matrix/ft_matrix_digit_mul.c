/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matrix_digit_mul.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgalyeon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 09:42:26 by rgalyeon          #+#    #+#             */
/*   Updated: 2019/03/15 00:55:37 by ggerardy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix_ft.h"

t_matrix	*ft_matrix_digit_mul(t_matrix *arr, double digit)
{
	size_t	i;
	size_t	j;

	if (!arr || !(arr->matrix) || (arr->row) == 0 || (arr->col) == 0)
		return (NULL);
	i = -1;
	while (++i < arr->row)
	{
		j = -1;
		while (++j < arr->col)
			(arr->matrix)[i][j] *= digit;
	}
	return (arr);
}
