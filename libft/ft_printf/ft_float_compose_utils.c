/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_float_compose.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehugh-be <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/31 18:42:46 by ehugh-be          #+#    #+#             */
/*   Updated: 2019/03/15 00:55:37 by ggerardy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_utils.h"

int				ft_find_whole_size(long double flt, long double *dec)
{
	int ret;

	*dec = 1;
	ret = 0;
	if (flt == 0 || flt == 1)
	{
		ret = 0;
	}
	else if (flt > 1.l)
		while (flt > 10.0l)
		{
			ret++;
			*dec *= 10.0;
			flt /= 10.0;
		}
	else if (flt < 1.l)
		while (flt < 1.0l)
		{
			ret--;
			*dec /= 10.0;
			flt *= 10.0;
		}
	return (ret);
}

long double		ft_find_whole(long double flt)
{
	t_bitld		ld;
	int			tmp;

	if (flt < 1.l && flt > -1.l)
		return (0);
	ld.d = flt;
	if ((ld.i >> 78 & 1) || (int)(((ld.i) >> 64) & 0x3FFF))
	{
		tmp = (int)(((ld.i) >> 64) & 0x3FFF);
		if (tmp < 61)
			ld.i = (ld.i >> (62 - tmp)) << (62 - tmp);
		else if (tmp == 0x3FFF)
			ld.i = (ld.i >> (63)) << (63);
	}
	else
		return (0);
	return (ld.d);
}

void			ft_dog(t_fc *fc, t_arg_data *ad)
{
	long double	dp;
	int			i;
	int			lp;

	lp = -1;
	i = 0;
	dp = fc->f;
	while (++i <= ad->prcsn)
	{
		dp *= 10.l;
		lp = (ft_find_whole(dp) != 0) ? i : lp;
		dp -= ft_find_whole(dp);
	}
	ad->prcsn = lp == -1 ? 0 : lp;
}

long double		ft_check_digit(long double n, int *p, int prec)
{
	static long double	ten = 10e18l;
	static int			prev = 9;
	unsigned long		i;

	if (prec > 18 && (*p = 1))
		return (n);
	i = (unsigned long)(n * ten);
	i %= 10;
	if (*p == -1)
	{
		prev = (int)i;
		ten = 10e18 - 1.l;
		*p = 1;
		return (n);
	}
	if ((i == 9 && prev == 0) || (i == 0 && prev == 9))
	{
		n = n + ((i == 9 && prev == 0) ? 1.l / ten : -1.l / ten);
	}
	ten /= 10.l;
	return (n);
}

void			ft_enot(t_fc *fc)
{
	long double cp;

	if (fc->w == 0)
	{
		cp = fc->f / fc->f_d;
		fc->w = ft_find_whole(cp);
		fc->f = cp - fc->w;
		fc->w_lg = fc->f_lg;
	}
	else
	{
		cp = fc->w / fc->w_d;
		fc->w = ft_find_whole(cp);
		fc->f = fc->f / fc->w_d + (cp - fc->w);
	}
}
