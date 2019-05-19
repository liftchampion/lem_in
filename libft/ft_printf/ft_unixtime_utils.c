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

#include "ft_unixtime.h"
#include <stdlib.h>

static char g_ms[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

int		ft_sub_hour(t_date *dt, long int *n)
{
	if (*n > -3600)
		return (0);
	*n += 3600;
	if (dt->hr == 0 && (dt->hr = 23))
		if (dt->day == 1 && (dt->day = g_ms[dt->mth] +
				(dt->mth == 1 && IS_LEAP_YEAR(dt->year))))
			if (dt->mth == 0 && (dt->mth = 11))
				--dt->year;
			else
				--dt->mth;
		else
			--dt->day;
	else
		--dt->hr;
	return (1);
}

int		ft_add_minute(t_date *dt, long int *n)
{
	if (*n < 60)
		return (0);
	*n -= 60;
	if (dt->min == 59 && !(dt->min = 0))
		if (dt->hr == 23 && !(dt->hr = 0))
			if (dt->day == g_ms[dt->mth] + (dt->mth == 1 &&
					IS_LEAP_YEAR(dt->year)) && (dt->day = 1))
				if (dt->mth == 11 && !(dt->mth = 0))
					++dt->year;
				else
					++dt->mth;
			else
				++dt->day;
		else
			++dt->hr;
	else
		++dt->min;
	return (1);
}

int		ft_sub_minute(t_date *dt, long int *n)
{
	if (*n > -60)
		return (0);
	*n += 60;
	if (dt->min == 00 && (dt->min = 59))
		if (dt->hr == 00 && (dt->hr = 23))
			if (dt->day == 1 && (dt->day = g_ms[dt->mth] +
					(dt->mth == 1 && IS_LEAP_YEAR(dt->year))))
				if (dt->mth == 0 && (dt->mth = 11))
					--dt->year;
				else
					--dt->mth;
			else
				--dt->day;
		else
			--dt->hr;
	else
		--dt->min;
	return (1);
}

int		ft_add_second(t_date *dt, long int *n)
{
	if (*n < 1)
		return (0);
	*n -= 1;
	if (dt->sec == 59 && !(dt->sec = 0))
		if (dt->min == 59 && !(dt->min = 0))
			if (dt->hr == 23 && !(dt->hr = 0))
				if (dt->day == g_ms[dt->mth] + (dt->mth == 1 &&
						IS_LEAP_YEAR(dt->year)) && (dt->day = 1))
					if (dt->mth == 11 && !(dt->mth = 0))
						++dt->year;
					else
						++dt->mth;
				else
					++dt->day;
			else
				++dt->hr;
		else
			++dt->min;
	else
		++dt->sec;
	return (1);
}

int		ft_sub_second(t_date *dt, long int *n)
{
	if (*n > -1)
		return (0);
	*n += 1;
	if (dt->sec == 0 && (dt->sec = 59))
		if (dt->min == 0 && (dt->min = 59))
			if (dt->hr == 0 && (dt->hr = 23))
				if (dt->day == 1 && (dt->day = g_ms[dt->mth] +
						(dt->mth == 1 && IS_LEAP_YEAR(dt->year))))
					if (dt->mth == 0 && (dt->mth = 11))
						--dt->year;
					else
						--dt->mth;
				else
					--dt->day;
			else
				--dt->hr;
		else
			--dt->min;
	else
		--dt->sec;
	return (1);
}
