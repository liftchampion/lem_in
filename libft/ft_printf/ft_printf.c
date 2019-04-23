/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehugh-be <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/16 22:36:59 by ehugh-be          #+#    #+#             */
/*   Updated: 2019/03/15 00:55:37 by ggerardy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_utils.h"

static int	ft_loop(const char *frmt, t_string **str, t_arg_data **vars,
		t_string *args_seq)
{
	int i;

	i = 0;
	while (*frmt)
	{
		if (!ft_find_cntrl(&frmt, &str[i]))
			return (-1);
		if (*(frmt - 1) == CLR_CNTRL && CLR)
		{
			if (ft_set_color(&frmt, &str[i]))
				return (-1);
			frmt += (*frmt != 0);
		}
		else
		{
			vars[i++] = ft_printf_parser(&frmt, &args_seq);
			str[i] = ft_make_string(4);
		}
	}
	return (*str ? 1 : -1);
}

t_string	*ft_vprintf(const char *frmt, va_list vl)
{
	t_string	*str[1000];
	t_string	*args_seq;
	t_arg_data	*vars[1000];
	int			i;

	ft_bzero(str, sizeof(t_string*) * 100);
	ft_bzero(vars, sizeof(t_arg_data*) * 99);
	args_seq = ft_make_string(32);
	str[0] = ft_make_string(64);
	if (ft_loop(frmt, str, vars, args_seq) == -1)
		return (0);
	ft_stringify(&(str[0]), vars, vl, args_seq);
	ft_free_string(&args_seq);
	i = -1;
	while (str[++i])
		if (i && str[i])
			ft_free_string(&str[i]);
	i = -1;
	while (vars[++i])
		if (vars[i])
			free(vars[i]);
	return ((*str));
}

int			ft_fdprintf(int fd, const char *frmt, ...)
{
	static int	b_strs[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	va_list		vl;
	t_string	*str;
	long int	ret;

	if (frmt >= 0 && (int)frmt < 10 &&
			((b_strs[(int)frmt] = !b_strs[(int)frmt]) || 1))
		return (0);
	if (frmt >= 0 && (int)frmt < 10 && b_strs[(int)frmt])
		return (0);
	va_start(vl, frmt);
	str = ft_vprintf(frmt, vl);
	ft_fd_print_string(str, fd);
	ret = str ? str->len : -1;
	ft_free_string(&str);
	va_end(vl);
	return ((int)ret);
}

int			ft_sprintf(char **buf, const char *frmt, ...)
{
	va_list		vl;
	t_string	*str;
	long int	ret;

	va_start(vl, frmt);
	str = ft_vprintf(frmt, vl);
	ret = str ? str->len : -1;
	*buf = str ? str->data : NULL;
	free(str);
	va_end(vl);
	return ((int)ret);
}

int			ft_printf(const char *frmt, ...)
{
	va_list		vl;
	t_string	*str;
	long int	ret;

	va_start(vl, frmt);
	str = ft_vprintf(frmt, vl);
	ft_print_string(str);
	ret = str ? str->len : -1;
	ft_free_string(&str);
	va_end(vl);
	return ((int)ret);
}
