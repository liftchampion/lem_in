/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matrix_print.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgalyeon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/02 03:35:46 by rgalyeon          #+#    #+#             */
/*   Updated: 2019/03/15 00:55:37 by ggerardy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "matrix_ft.h"

void	ft_matrix_print(t_matrix *mass, int prec)
{
	size_t	i;
	size_t	j;
	int		k;
	int		len;

	i = -1;
	len = ft_intlen((int)ft_matrix_max(mass));
	while (++i < mass->row)
	{
		j = -1;
		while (++j < mass->col)
		{
			k = ft_intlen((mass->matrix)[i][j]);
			ft_putchar('[');
			while (k++ < len)
				ft_putchar(' ');
			ft_putstr(ft_ftoa(mass->matrix[i][j], prec));
			ft_putchar(']');
		}
		ft_putchar('\n');
	}
}
