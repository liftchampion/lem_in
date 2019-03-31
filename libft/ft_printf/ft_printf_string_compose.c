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

#include "ft_printf_utils.h"
#include "ft_printf.h"

int			ft_guf(int *str, int prec)
{
	int p;

	p = 0;
	while (*str && prec > ft_unilen(*str) - 1)
	{
		p += ft_unilen(*str);
		prec -= ft_unilen(*str);
		str++;
	}
	return (p);
}

int			ft_prcd_non_prntbl_str(const char *str, int prec, t_string **res,
		char psh)
{
	int		p;
	char	buf[6];
	char	use_len;

	p = 0;
	use_len = (prec == DEFAULT_STRING_PRECISION) ? (char)1 : (char)0;
	while ((buf[0] = '\\') && (*str++ || !use_len) && prec-- > 0)
		if (ft_isprint(*(str - 1)) && (p += 1))
		{
			PUSH_S(res, psh == 2 ? "\e[39m" : 0);
			PUSH_C(res, psh ? *(str - 1) : 0);
		}
		else if ((*(str - 1) == '\n' || *(str - 1) == '\t') && (p += 2))
		{
			PUSH_S(res, psh == 2 ? "\e[33m" : 0);
			PUSH_S(psh ? res : 0, (*(str - 1) == '\n') ? "\\n" : "\\t");
		}
		else if ((p += ft_intlen(*(str - 1)) + 1))
		{
			PUSH_S(res, psh == 2 ? "\e[33m" : 0);
			PUSH_S(res, psh ? ft_itoa_buf(*(str - 1), buf + 1) - 1 : 0);
		}
	PUSH_S(res, (psh == 2 && prec > 0) ? "\e[33m" : 0);
	PUSH_S(res, (prec > 0 && (p += 2) && psh) ? "\\0" : 0);
	return (PUSH_S(res, psh == 2 ? "\e[39m" : 0) * 0 + p);
}

size_t		srle(const char *s, char f, int prec)
{
	size_t ln;

	ln = (f == 's') ? ft_strlen((char*)s) : 0;
	ln = (f == 'c') ? 1 : ln;
	ln = (f == 'S') ? ft_strlen_u((const int*)s, 0) : ln;
	ln = (f == 'C') ? ft_unilen((int)s) : ln;
	ln = (f == 's' && prec < (int)ln) ? prec : ln;
	ln = (f == 'S' && prec < (int)ln) ? ft_guf((int*)s, prec) : ln;
	ln = (f == 'r') ? ft_prcd_non_prntbl_str(s, prec, 0, 0) : ln;
	return (ln);
}

int			ft_printf_string_compose(t_arg_data *ad, char **a, t_string **str)
{
	size_t		ln;
	char		uni[5];
	static char	*n = "(null)";

	a = !*a && (ft_tolower(ad->frt) == 's' || ad->frt == 'r') ? &n : a;
	ad->frt = (a == &n) ? (char)'s' : ad->frt;
	ln = srle(*a, ad->frt, ad->prcsn);
	ad->frt = (ad->frt == 'C' && !*(int*)a) ? (char)'c' : ad->frt;
	if (!ad->l_a)
		PUSH_NC(str, ad->wdth - ln, ad->ac);
	if (ft_tolower(ad->frt) == 'c')
		ad->frt == 'C' ? PUSH_S(str, ft_int_to_unicode(*(int*)a, uni)) :
												PUSH_C(str, (char)*a);
	else if (ad->frt == 'S')
		while (**(int**)a && ad->prcsn > ft_unilen(*(int*)*a) - 1 && (*a += 4))
			ad->prcsn -= PUSH_S(str,
					ft_int_to_unicode(*(int*)(*a - 4), uni));
	else if (ad->frt == 'r')
		ft_prcd_non_prntbl_str(*a, ad->prcsn, str, (ad->alt != 0) + 1);
	else
		ad->prcsn >= 0 ? PUSH_NS(str, *a, ad->prcsn) : PUSH_S(str, *a);
	if (ad->l_a)
		PUSH_NC(str, ad->wdth - ln, ad->ac);
	return (*str ? 1 : 0);
}
