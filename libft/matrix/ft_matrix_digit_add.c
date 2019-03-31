/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shapka.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgalyeon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/14 21:31:45 by rgalyeon          #+#    #+#             */
/*   Updated: 2019/03/15 00:55:37 by ggerardy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"
#include "matrix_ft.h"

t_matrix	*ft_matrix_digit_add(t_matrix *mtx, double dig)
{
	size_t	i;
	size_t	j;

	i = -1;
	while (++i < mtx->row)
	{
		j = -1;
		while (++j < mtx->col)
		{
			if (j != 3)
				mtx->matrix[i][j] += dig;
		}
	}
	return (mtx);
}
