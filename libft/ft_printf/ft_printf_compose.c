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

void	ft_push_all(t_fc *fc, t_arg_data *ad, t_string **str)
{
	int		pad;
	char	buf[10];

	buf[0] = '0';
	pad = (ad->sign != 0) + ((ft_tolower(ad->frt) == 'e') ?
			(3 + ft_intlen(FT_ABS(fc->w_lg)) + (fc->w_lg > -10 && fc->w_lg < 10)
			+ (ad->prcsn != 0 || ad->alt) + ad->prcsn) : (fc->w_lg + 1 +
			(ad->prcsn != 0 || ad->alt) + ad->prcsn));
	ft_string_push_back((ad->sign && ad->ac == '0') ? str : 0, ad->sign);
	if (!ad->l_a)
		ft_string_push_back_n_c(str, ad->wdth - pad, ad->ac);
	ft_string_push_back((ad->sign && ad->ac == ' ') ? str : 0, ad->sign);
	ft_push_part(fc, -1, str);
	ft_string_push_back((ad->prcsn || ad->alt) ? str : 0, '.');
	ft_push_part(fc, ad->prcsn, str);
	if (ft_tolower(ad->frt) == 'e')
	{
		ft_string_push_back(str, ad->frt);
		ft_string_push_back(str, fc->w_lg >= 0 ? (char)'+' : (char)'-');
		fc->w_lg = FT_ABS(fc->w_lg);
		ft_string_push_back_s(str, ft_itoa_buf(fc->w_lg, buf +
				(fc->w_lg < 10)) - (fc->w_lg < 10));
	}
	if (ad->l_a)
		ft_string_push_back_n_c(str, ad->wdth - pad, ad->ac);
}

int		ft_printf_float_compose(t_arg_data *ad, void *arg, t_string **str)
{
	long double	flt;
	t_fc		*dt;

	flt = ad->size == DEFAULT ? *(double*)arg : *(long double*)arg;
	if (ft_check_nan(&flt, ad, str))
		return (*str ? 1 : 0);
	if (!(dt = ft_fc_maker(ad, &flt)))
		return (0);
	ft_push_all(dt, ad, str);
	free(dt);
	return (*str ? 1 : 0);
}

void	ft_printf_final_arg_data_checks(t_arg_data *ad, char type)
{
	if (ad->wdth < 0 && (ad->l_a = 1))
		ad->wdth *= -1;
	if (ad->l_a || ad->frt == 'k')
		ad->ac = ' ';
	if (type == 'g')
	{
		if (ad->prcsn == DEFAULT)
			ad->prcsn = (ft_strchr("sSr", ad->frt)) ?
						DEFAULT_STRING_PRECISION : DEFAULT_INT_PRECISION;
		else if (!ft_strchr("cCsSr", ad->frt))
			ad->ac = ' ';
		if (ad->ac == '0' && !ft_strchr("cCsSrk", ad->frt))
		{
			ad->prcsn = ad->wdth ? ad->wdth : 1;
			ad->wdth = -1;
		}
	}
	else if (type == 'f')
	{
		if (ad->prcsn == DEFAULT)
			ad->prcsn = DEF_F_PRCSN;
		if (ad->prcsn == 0)
			ad->prcsn = ft_tolower(ad->frt) == 'g' ? 1 : 0;
	}
}

int		ft_printf_compose(t_arg_data *arg_dat, void *arg, t_string **str,
		char type)
{
	ft_printf_final_arg_data_checks(arg_dat, type);
	if (type == 'g' && !ft_strchr("sScCrk", arg_dat->frt))
		return (ft_printf_int_compose(arg_dat, arg, str));
	else if (type == 'g' && !ft_strchr("kn", arg_dat->frt))
		return (ft_printf_string_compose(arg_dat, (char**)arg, str));
	else if (type == 'g' && arg_dat->frt == 'k')
		return (ft_printf_date_compose(arg_dat, arg, str));
	else if (type == 'g' && arg_dat->frt == 'n')
		return ((**(int**)arg = (int)(*str)->len) * 0 + 1);
	else if (type == 'f')
		return (ft_printf_float_compose(arg_dat, arg, str));
	return (0);
}
