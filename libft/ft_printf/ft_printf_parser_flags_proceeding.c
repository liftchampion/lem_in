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

#include "ft_printf.h"
#include "ft_printf_utils.h"

int		ft_parse_len_specifier(const char **frmt, int lengths[4])
{
	if (**frmt == 'h' && *(*frmt)++)
		H_COUNT++;
	else if (**frmt == 'l' && *(*frmt)++)
		L_COUNT++;
	else if ((**frmt == 'j' || **frmt == 'z') && *(*frmt)++)
		L_COUNT += 2;
	else if (**frmt == 'L' && *(*frmt)++)
		BIG_L_COUNT++;
	else if (**frmt == _128_SPECIFIER && *(*frmt)++)
		_128_COUNT++;
	else
		return (0);
	return (1);
}

int		ft_printf_parse_modifiers(const char **frmt, t_arg_data *arg_data)
{
	int was_found;

	was_found = 0;
	if (**frmt == ' ' && ++was_found && *(*frmt)++ && !arg_data->sign)
		arg_data->sign = ' ';
	else if (**frmt == '+' && ++was_found && *(*frmt)++)
		arg_data->sign = '+';
	else if (**frmt == '0' && ++was_found)
		arg_data->ac = *(*frmt)++;
	else if (**frmt == '-' && ++was_found && *(*frmt)++)
		arg_data->l_a = 1;
	else if (**frmt == '#' && ++was_found && *(*frmt)++)
		arg_data->alt = 1;
	else if ((**frmt == '\'' || **frmt == ',') && ++was_found)
		arg_data->spl = *(*frmt)++;
	else if (**frmt == '.' && ++was_found && *(*frmt)++)
	{
		arg_data->was_dot = 1;
		if (**frmt != '*')
			ft_printf_arg_data_set_width_or_prec(arg_data, ft_atoi_m(frmt));
	}
	return (was_found);
}

int		ft_printf_parse_simple_flags(const char **frmt, t_arg_data *arg_data,
		int lengths[4])
{
	int was_found_iter;
	int was_found_total;

	was_found_iter = 1;
	was_found_total = 0;
	while (was_found_iter)
	{
		was_found_iter = 0;
		was_found_iter += ft_parse_len_specifier(frmt, lengths);
		was_found_iter += ft_printf_parse_modifiers(frmt, arg_data);
		was_found_total += was_found_iter;
	}
	return (was_found_total ? 1 : 0);
}

int		ft_printf_parser_comlex_flags_proceeder(t_arg_data *arg_data,
				t_complex_flags_data *flags_data, t_string **args, int *n_arg)
{
	if (flags_data->was_star && flags_data->num > 0 && flags_data->was_dollar)
	{
		if (!ft_string_set_value(args, (size_t)flags_data->num - 1, 'g', 'g'))
			return ((*n_arg = -1) + 1);
		ft_printf_arg_data_set_width_or_prec(arg_data, -1 * flags_data->num);
	}
	else if (flags_data->was_star && !flags_data->was_dollar)
	{
		if (!ft_string_set_value(args, (size_t)*n_arg - 1, 'g', 'g'))
			return ((*n_arg = -1) + 1);
		ft_printf_arg_data_set_width_or_prec(arg_data, -1 * *n_arg);
		(*n_arg)++;
		if (flags_data->num > 0)
			ft_printf_arg_data_set_width_or_prec(arg_data, flags_data->num);
	}
	else if (!flags_data->was_star && flags_data->num > 0 &&
			flags_data->was_dollar)
		*n_arg = flags_data->num;
	else if (!flags_data->was_star && flags_data->num > 0 &&
			!flags_data->was_dollar)
		ft_printf_arg_data_set_width_or_prec(arg_data, flags_data->num);
	return (1);
}

int		ft_printf_parse_comlex_flags(const char **frmt, t_arg_data *arg_data,
													t_string **args, int *n_arg)
{
	int was_star;
	int num;
	int was_dollar;
	int was_zero;

	was_star = (**frmt == '*' && *(*frmt)++) ? 1 : 0;
	was_zero = **frmt == '0' ? 1 : 0;
	num = ft_isdigit(**frmt) ? ft_atoi_m(frmt) : -1;
	was_dollar = ((**frmt == '$' && num + was_star > 0) && *(*frmt)++) ? 1 : 0;
	was_zero = (was_zero && !(was_star && was_dollar)) ? 1 : 0;
	if (!ft_printf_parser_comlex_flags_proceeder(arg_data,
			&(t_complex_flags_data){was_star, num, was_dollar, was_zero},
			args, n_arg))
	{
		return (0);
	}
	arg_data->ac = was_zero ? (char)'0' :
								arg_data->ac;
	return ((num + 1 || was_star || was_dollar) ? 1 : 0);
}
