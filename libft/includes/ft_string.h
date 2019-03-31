/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_string.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggerardy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/13 02:00:02 by ggerardy          #+#    #+#             */
/*   Updated: 2019/03/15 00:55:37 by ggerardy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_STRING_H
# define FT_STRING_H

# include <stdlib.h>
# include "libft.h"

typedef struct	s_string
{
	char		*data;
	size_t		len;
	size_t		capacity;
	int			offset;
}				t_string;

typedef struct	s_vector
{
	void		**data;
	size_t		len;
	size_t		capacity;
	int			offset;
}				t_vector;

t_vector		*ft_make_vector(size_t init_size);
t_vector		*ft_vector_cpy(const t_vector *src);
void			ft_free_vector(t_vector **v);
t_int8			ft_vector_push_back(t_vector **v_ptr, void *c);
t_int8			ft_vector_fit(t_vector **v_ptr);

void			ft_print_string(t_string *str);
void			ft_fd_print_string(t_string *str, int fd);

void			ft_free_string(t_string **str);

int				ft_string_fit(t_string **str);

int				ft_string_push_back(t_string **str, char c);
int				ft_string_push_back_s(t_string **str_ptr, char *str);
int				ft_string_push_back_n_s(t_string **str_ptr, char *str,
		size_t n);
int				ft_string_push_back_n_c(t_string **str_ptr,
		long n, char c);

int				ft_string_set_value(t_string **str, size_t n, char filler,
		char value);
t_string		*ft_make_string(size_t init_size);

#endif
