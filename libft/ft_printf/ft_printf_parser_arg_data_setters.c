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
#include "libft.h"

void			ft_printf_arg_data_set_width_or_prec(t_arg_data *arg_data,
																		int n)
{
	if (!arg_data->was_dot)
	{
		arg_data->wdth = n;
	}
	else
	{
		arg_data->prcsn = n;
		arg_data->was_dot = 0;
	}
}

t_arg_sz		ft_printf_parser_get_int_arg_size(char c, const int lengths[4])
{
	if (ft_strchr(LONG_INT_TYPE_SPECS, c))
		return (LONG);
	else if ((c == 'c' && L_COUNT % 2) || c == 'C')
		return (DEFAULT);
	else if (c == 'c')
		return (CHAR_P);
	else if (_128_COUNT)
		return (_INT128);
	else if (L_COUNT)
		return (LONG);
	else if (H_COUNT % 2)
		return (SHORT);
	else if (H_COUNT)
		return (CHAR_P);
	else
		return (DEFAULT);
}

int				ft_set_int_arg_data(t_arg_data *arg_data, char c,
											t_string **args, int lengths[4])
{
	arg_data->size = ft_printf_parser_get_int_arg_size(c, lengths);
	if ((c == 'c' && arg_data->size == DEFAULT) || (c == 's' && L_COUNT % 2))
		arg_data->frt = (c == 'c') ? (char)'C' : (char)'S';
	else
		arg_data->frt = c;
	if (!ft_string_set_value(args, (size_t)(arg_data->num) - 1, 'g',
			arg_data->size == _INT128 ? (char)'G' : (char)'g'))
		return (0);
	return (1);
}

int				ft_set_float_arg_data(t_arg_data *arg_data, char c,
												t_string **args, int lengths[4])
{
	arg_data->size = BIG_L_COUNT ? LONG : DEFAULT;
	arg_data->frt = c;
	if (!ft_string_set_value(args, (size_t)(arg_data->num) - 1, 'g',
			arg_data->size == LONG ? (char)'F' : (char)'f'))
	{
		return (0);
	}
	return (1);
}

void			ft_set_invalid_arg_data(t_arg_data *arg_data, char c,
																t_string **args)
{
	arg_data->size = CHAR_P;
	arg_data->frt = 'c';
	arg_data->char_arg = c;
	arg_data->num = -1;
	--(*args)->offset;
}
