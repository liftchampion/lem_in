/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shapka.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggerardy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 17:25:22 by ggerardy          #+#    #+#             */
/*   Updated: 2019/03/15 00:55:37 by ggerardy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_TYPES_H
# define FT_TYPES_H

# include <string.h>

typedef char					t_int8;
typedef unsigned char			t_uint8;

typedef short int				t_int16;
typedef unsigned short int		t_uint16;

typedef int						t_int32;
typedef unsigned int			t_uint32;

typedef long long int			t_int64;
typedef unsigned long long int	t_uint64;

typedef int						(*t_cmp_func)(void*, void*);
typedef void					(*t_del_func)(void*);

typedef enum {
	INT8_T,
	UINT8_T,
	INT16_T,
	UINT16_T,
	INT32_T,
	UINT32_T,
	INT64_T,
	UINT64_T,
	SIZE_T,
	SSIZE_T,
	CHAR,
	STRING,
	ARRAY,
	VECTOR,
	V_STRING,
	CUSTOM
}	t_type;

int				ft_cmp_int8(void *a, void *b);
int				ft_cmp_int16(void *a, void *b);
int				ft_cmp_int32(void *a, void *b);
int				ft_cmp_int64(void *a, void *b);
int				ft_cmp_ssize_t(void *a, void *b);

int				ft_cmp_uint8(void *a, void *b);
int				ft_cmp_uint16(void *a, void *b);
int				ft_cmp_uint32(void *a, void *b);
int				ft_cmp_uint64(void *a, void *b);
int				ft_cmp_size_t(void *a, void *b);

int				ft_cmp_char(void *a, void *b);
int				ft_cmp_str(void *v1, void *v2);

t_cmp_func		ft_get_cmp_func(t_type type);
t_del_func		ft_get_del_func(t_type type);

#endif
