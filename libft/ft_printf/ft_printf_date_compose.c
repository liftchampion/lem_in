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
#include "ft_unixtime.h"

char		*ft_printf_date_compose_get_str(t_date *dt, void *arg,
		t_arg_data *ad)
{
	char		*res;
	char		buf[50];
	char		use_year;
	static char	mths[12][4] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun",
								"Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};

	ft_bzero(buf, 50);
	res = 0;
	if (ad->alt &&
		((use_year = (FT_ABS(*(long*)arg - ad->prcsn) > HALF_YEAR)) + 1))
		ft_sprintf(&res, ft_strcat(ft_strcat(buf, "%s %2d "), use_year ? "%5d" :
		"%02d:%02d"), mths[dt->mth], dt->day, use_year ? dt->year : dt->hr,
				dt->min);
	else if (++dt->mth && (ad->size == DEFAULT || ad->size == LONG))
		ad->size == DEFAULT ? ft_sprintf(&res, "%4d-%02d-%02d %02d:%02d",
				dt->year, dt->mth, dt->day, dt->hr, dt->min) :
				ft_sprintf(&res, "%4d-%02d-%02d %02d:%02d:%02d", dt->year,
				dt->mth, dt->day, dt->hr, dt->min, dt->sec);
	else if (ad->size == SHORT || ad->size == CHAR_P)
		ad->size == SHORT ? ft_sprintf(&res, "%4d-%02d-%02d", dt->year, dt->mth,
				dt->day) : ft_sprintf(&res, "%4d-%02d", dt->year, dt->mth);
	return (res);
}

int			ft_printf_date_compose(t_arg_data *ad, void *arg, t_string **str)
{
	t_date	*dt;
	char	*res;

	dt = ft_unix_time_to_date(*(long int*)arg);
	res = ft_printf_date_compose_get_str(dt, arg, ad);
	if (!ad->l_a)
		ft_string_push_back_n_c(str, ad->wdth - ft_strlen(res), ad->ac);
	ft_string_push_back_s(str, res);
	if (ad->l_a)
		ft_string_push_back_n_c(str, ad->wdth - ft_strlen(res), ad->ac);
	free(dt);
	free(res);
	return (1);
}
