/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_ft.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgalyeon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/07 18:53:33 by rgalyeon          #+#    #+#             */
/*   Updated: 2019/03/15 00:55:37 by ggerardy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATRIX_FT_H
# define MATRIX_FT_H
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include "libft.h"

typedef struct	s_matrix
{
	double	**matrix;
	size_t	row;
	size_t	col;
}				t_matrix;

t_matrix		*ft_matrix_create(size_t m, size_t n);
t_matrix		*ft_matrix_copy(t_matrix *arr);
t_matrix		*ft_matrix_digit_mul(t_matrix *arr, double digit);
t_matrix		*ft_matrix_mul(t_matrix *a, t_matrix *b);
t_matrix		*ft_matrix_add(t_matrix *a, t_matrix *b);
t_matrix		*ft_matrix_trans(t_matrix *a);
double			ft_matrix_max(t_matrix *a);
void			ft_matrix_print(t_matrix *a, int prec);
t_matrix		*ft_matrix_digit_add(t_matrix *mtx, double dig);

#endif
