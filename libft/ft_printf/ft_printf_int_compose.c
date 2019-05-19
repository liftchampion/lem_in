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

#include <stdlib.h>
#include "ft_printf_utils.h"

static char				*ft_printf_get_bits(unsigned long n, t_arg_data *ad)
{
	int			len;
	char		*ret;
	int			i;
	t_arg_sz	sz;

	ad->wdth = (ad->wdth == -1) ? 0 : ad->wdth;
	i = 0;
	sz = (ad->size == DEFAULT) ? 4 : ad->size;
	len = sz * 8 + sz - 1;
	if (!(ret = ft_memalloc(len + 1 + 5 * 75 * (ad->alt != 0))))
		return (0);
	len -= (sz - 1) + 1;
	while (len >= 0)
	{
		if (ad->alt && (i += 5))
			ft_strlcat(ret, (n & (1L << len)) != 0 ? "\e[31m" : "\e[39m", 600);
		ret[i++] = (char)'0' + ((n & (1L << len)) != 0);
		if (len-- && (len + 1) % 8 == 0)
		{
			ft_strlcat(ret, (ad->alt && (i += 5)) ? "\e[39m" : "", 600);
			ret[i++] = ad->spl ? ad->spl : (char)' ';
		}
	}
	ft_strlcat(ret, (ad->alt) ? "\e[39m" : "", 600);
	return (ret);
}

static unsigned long	ft_printf_int_caster(void *n, t_arg_sz sz, char us,
		char *sign)
{
	*sign = us ? (char)0 : *sign;
	if (sz == CHAR_P && (us || ((*(char*)n < 0 && (*sign = '-'))) ||
															(*(char*)n >= 0)))
		return (us ? *(unsigned char*)n :
					(unsigned char)(*(char*)n * (1 - 2 * (*sign == '-'))));
	else if (sz == SHORT && (us || ((*(short*)n < 0 && (*sign = '-'))) ||
															(*(short*)n >= 0)))
		return (us ? *(unsigned short*)n :
					(unsigned short)(*(short*)n * (1 - 2 * (*sign == '-'))));
	else if (sz == DEFAULT && (us || ((*(int*)n < 0 && (*sign = '-'))) ||
															(*(int*)n >= 0)))
		return (us ? *(unsigned int*)n :
					(unsigned int)(*(int*)n * (1 - 2 * (*sign == '-'))));
	else if (sz == LONG && (us || ((*(long*)n < 0 && (*sign = '-'))) ||
															(*(long*)n >= 0)))
		return (us ? *(unsigned long*)n :
					(unsigned long)(*(long*)n * (1 - 2 * (*sign == '-'))));
	else
		return (*(unsigned long*)n);
}

static char				*ft_printf_itoa_pro(unsigned long n, int r,
		t_arg_data *ad)
{
	static char		bas[] = "0123456789ABCDEF";
	int				l;
	char			*ret;
	unsigned long	nb;
	int				i;

	if (r == -2)
		return (ft_printf_get_bits(n, ad));
	if (r == 16 || r == -16)
		(r < 0 && (r *= -1)) ? ft_tolower_str(bas) : ft_toupper_str(bas);
	l = 1 + (n != 0 || ad->prcsn) + (ad->sign && r == 10);
	nb = n;
	while (nb >= (unsigned long)r && l++)
		nb /= r;
	l += ((l - 2) / 3) * ((i = 1) && ad->spl != 0 && (r == 10 || r == 8));
	ad->prcsn = ((l - !n > ad->prcsn) && r == 8 && ad->alt) ? l : ad->prcsn;
	ad->prcsn += (ad->wdth == -1 && (ad->wdth = 1)) ? 0 : (ad->sign && r == 10);
	l = (ad->prcsn + 1 > l) ? (ad->prcsn + 1) : l;
	if (!(ret = (char *)ft_memalloc(sizeof(char) * l--)))
		return (NULL);
	while ((n || l) && (ret[--l] = bas[(n % r)]))
		if (((n /= r) + 1) && n && !(i++ % 3) && ad->spl && (r == 10 || r == 8))
			ret[--l] = ad->spl;
	ret[0] = (ad->sign && r == 10) ? ad->sign : ret[0];
	return (ret);
}

static int				ft_printf_get_itoa_radix(char c)
{
	if (ft_strchr("dDuUiI", c))
		return (10);
	else if (c == 'b' || c == 'B')
		return (c == 'b' ? 2 : -2);
	else if (c == 'o' || c == 'O')
		return (8);
	else if (c == 'x' || c == 'X' || c == 'p')
		return ((c == 'x' || c == 'p') ? -16 : 16);
	else
		return (10);
}

int						ft_printf_int_compose(t_arg_data *ad, void *arg,
													t_string **str)
{
	char			*res;
	char			us;
	size_t			len;
	int				nex;
	unsigned long	ar;

	us = ft_strchr("puUxXoObB", ad->frt) != 0;
	ar = ft_printf_int_caster(arg, ad->size, us, &ad->sign);
	nex = (ft_strchr("xXp", ad->frt) && ((ar != 0
			&& ad->alt) || ad->frt == 'p')) ? 1 : 0;
	ad->prcsn += ((ad->prcsn == 0) && (ft_tolower(ad->frt) == 'o') &&
			ad->alt) - (nex && ad->wdth == -1 && (ad->wdth = 1)) * 2;
	res = ft_printf_itoa_pro(ar, ft_printf_get_itoa_radix(ad->frt), ad);
	len = ft_strlen(res);
	if (!ad->l_a)
		ft_string_push_back_n_c(str, ad->wdth - len - nex * 2, ad->ac);
	if (nex)
		ft_string_push_back_s(str, ad->frt == 'X' ? "0X" : "0x");
	ft_string_push_back_s(str, res);
	if (ad->l_a)
		ft_string_push_back_n_c(str, ad->wdth - len - nex * 2, ad->ac);
	free(res);
	return ((*str || !res) ? 1 : 0);
}
