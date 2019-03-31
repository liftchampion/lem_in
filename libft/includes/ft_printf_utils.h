/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehugh-be <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/16 22:40:21 by ehugh-be          #+#    #+#             */
/*   Updated: 2019/03/15 00:55:37 by ggerardy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_UTILS_H
# define FT_PRINTF_UTILS_H

# include <stdarg.h>
# include "libft.h"
# include "ft_printf.h"

# define _128_SPECIFIER '_'
# define FT_SEPARATOR ','

# define DEF_F_PRCSN 6
# define DEFAULT_INT_PRECISION 1
# define DEFAULT_STRING_PRECISION 2147483647

# define INT_TYPE_SPECIFIERS "dDiIuUcCsSrpkxXoObBn"
# define FLOAT_TYPE_SPECIFIERS "fFeEgG"
# define LONG_INT_TYPE_SPECS "sprSDUIO"

# define SET_DEFAULT_LENGTHS lengths[0] = 0; lengths[1] = 0; lengths[2] = 0
# define _128_COUNT lengths[3]
# define H_COUNT lengths[2]
# define L_COUNT lengths[1]
# define BIG_L_COUNT lengths[0]

# define PUSH_S ft_string_push_back_s
# define PUSH_C ft_string_push_back
# define PUSH_NC ft_string_push_back_n_c
# define PUSH_NS ft_string_push_back_n_s

typedef struct	s_complex_flags_data
{
	int was_star;
	int num;
	int was_dollar;
	int was_zero;
}				t_complex_flags_data;

typedef struct	s_fc
{
	long double	w;
	long double	w_d;
	long double	f;
	long double	f_d;
	int			f_lg;
	int			w_lg;
}				t_fc;

typedef union	u_bitld
{
	long double d;
	__uint128_t i;
}				t_bitld;

typedef	enum	e_arg_sz
{
	CHAR_P = 1,
	SHORT = 2,
	LONG = 8,
	_INT128 = 16,
	DEFAULT = -2147481337,
}				t_arg_sz;

typedef struct	s_arg_data
{
	int			wdth;
	int			prcsn;
	char		l_a;
	char		ac;
	char		sign;
	char		alt;
	char		spl;
	int			num;
	t_arg_sz	size;
	char		char_arg;
	char		frt;
	char		was_dot;
}				t_arg_data;

t_arg_data		*ft_printf_parser(const char **frmt, t_string **args);
int				ft_printf_parse_simple_flags(const char **frmt,
										t_arg_data *arg_data, int *lenghts);
int				ft_parse_len_specifier(const char **frmt, int *lenghts);
int				ft_printf_parse_modifiers(const char **frmt,
														t_arg_data *arg_data);
int				ft_printf_parse_comlex_flags(const char **frmt,
							t_arg_data *arg_data, t_string **args, int *n_arg);
int				ft_printf_parser_comlex_flags_proceeder(t_arg_data *arg_data,
				t_complex_flags_data *flags_data, t_string **args, int *n_arg);
void			ft_printf_arg_data_set_width_or_prec(t_arg_data *arg_data,
																		int n);
t_arg_sz		ft_printf_parser_get_arg_size(char c, int lengths[4]);
int				ft_set_int_arg_data(t_arg_data *arg_data, char c,
											t_string **args, int lengths[4]);
int				ft_set_float_arg_data(t_arg_data *arg_data, char c,
											t_string **args, int lengths[4]);
void			ft_set_invalid_arg_data(t_arg_data *arg_data, char c,
															t_string **args);

int				ft_find_cntrl(const char **frmt, t_string **str);
int				ft_set_color(const char **frmt, t_string **str);
t_arg_data		*ft_printf_parser(const char **frmt, t_string **args);
int				ft_stringify(t_string **str, t_arg_data *v[], va_list vl,
		t_string *a_s);
void			*ft_get_va(int num, va_list vl, t_string *a_s);
void			ft_gen_compose(t_arg_data *v, void *num, t_string **str);
int				ft_printf_float_compose(t_arg_data *ad, void *n,
		t_string **str);
int				ft_printf_compose(t_arg_data *arg_dat, void *arg,
		t_string **str, char type);
int				ft_printf_int_compose(t_arg_data *ad, void *arg,
		t_string **str);
int				ft_printf_string_compose(t_arg_data *ad, char **a,
		t_string **str);
int				ft_printf_date_compose(t_arg_data *ad, void *arg,
		t_string **str);

t_fc			*ft_fc_maker(t_arg_data *ad, long double *arg);
int				ft_get_exp(t_fc fc, t_arg_data *ad);
int				ft_check_nan(long double *n, t_arg_data *ad, t_string **str);
void			ft_push_all(t_fc *fc, t_arg_data *ad, t_string **str);
void			ft_push_part(t_fc *fc, int prc, t_string **str);
void			ft_enot(t_fc *fc);
void			ft_tor(t_fc *fc, t_arg_data *ad);
void			ft_dog(t_fc *fc, t_arg_data *ad);
long double		ft_find_whole(long double flt);
int				ft_find_whole_size(long double flt, long double *dec);
long double		ft_check_digit(long double n, int *p, int prec);

#endif
