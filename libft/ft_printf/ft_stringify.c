/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stringify.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehugh-be <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/27 03:00:46 by ehugh-be          #+#    #+#             */
/*   Updated: 2019/03/15 00:55:37 by ggerardy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_utils.h"

static void	ft_vl_to_p(va_list vl, t_string *a_s, void *vl_p[])
{
	int i;

	i = -1;
	while ((a_s->data)[++i])
	{
		if (a_s->data[i] == 'F')
		{
			vl_p[i] = vl->overflow_arg_area;
			va_arg(vl, long double);
		}
		else if (a_s->data[i] == 'f')
		{
			vl_p[i] = (vl->fp_offset < 176) ? vl->reg_save_area + vl->fp_offset
					: vl->overflow_arg_area;
			va_arg(vl, double);
		}
		else
		{
			vl_p[i] = (vl->gp_offset < 48) ? vl->reg_save_area + vl->gp_offset
											: vl->overflow_arg_area;
			va_arg(vl, long);
		}
	}
}

static void	ft_loop(t_string **str, t_arg_data *v[], void **vl_p, t_string *a_s)
{
	int i;

	i = 0;
	while (1)
	{
		if (!str[i] || !v[i] || v[i]->frt == 0)
			break ;
		if (v[i]->wdth < 0)
			v[i]->wdth = *(int*)vl_p[-v[i]->wdth - 1];
		if (v[i]->prcsn < 0 && v[i]->prcsn != DEFAULT)
			v[i]->prcsn = *(int*)vl_p[-v[i]->prcsn - 1] >= 0 ?
				*(int*)vl_p[-v[i]->prcsn - 1] : DEFAULT;
		if (v[i]->char_arg)
			ft_printf_compose(v[i], &v[i]->char_arg, str, 'g');
		else
			ft_printf_compose(v[i], vl_p[v[i]->num - 1], str,
					(char)ft_tolower(a_s->data[v[i]->num - 1]));
		i++;
		ft_string_push_back_s(str, str[i]->data);
	}
}

int			ft_stringify(t_string **str, t_arg_data *v[], va_list vl,
		t_string *a_s)
{
	void	**vl_p;

	vl_p = malloc(sizeof(void *) * a_s->len);
	if (!str || !*str || !vl_p || !a_s || !v || !*v)
	{
		free(vl_p);
		return (-1);
	}
	ft_vl_to_p(vl, a_s, vl_p);
	ft_loop(str, v, vl_p, a_s);
	free(vl_p);
	return (*str ? 1 : -1);
}
