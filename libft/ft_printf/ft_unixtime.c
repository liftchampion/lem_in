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

int			ft_upd_year(t_date *dt, long int *n)
{
	if ((*n < (IS_LEAP_YEAR(dt->year) + 365) * DAY && *n >= 0) ||
			(*n > -1 * (IS_LEAP_YEAR(dt->year - 1) + 365) * DAY && *n < 0))
		return (0);
	if (*n > 0)
	{
		*n -= (IS_LEAP_YEAR(dt->year) + 365) * DAY;
		++dt->year;
		return (1);
	}
	*n += (IS_LEAP_YEAR(dt->year - 1) + 365) * DAY;
	--dt->year;
	return (1);
}

int			ft_upd_month(t_date *dt, long int *n)
{
	if ((*n < (g_ms[dt->mth] + (dt->mth == 1 && IS_LEAP_YEAR(dt->year))) * DAY
			&& *n >= 0) || (*n > -1 *
			(g_ms[dt->mth] + (dt->mth == 1 && IS_LEAP_YEAR(dt->year))) * DAY
			&& *n < 0))
		return (0);
	if (*n > 0)
	{
		if (*n < (g_ms[dt->mth] + (dt->mth == 1 &&
									IS_LEAP_YEAR(dt->year))) * DAY)
			return (0);
		*n -= (g_ms[dt->mth] + (dt->mth == 1 && IS_LEAP_YEAR(dt->year))) * DAY;
		if (dt->mth == 11 && !(dt->mth = 0))
			++dt->year;
		else
			++dt->mth;
		return (1);
	}
	if (*n < (g_ms[dt->mth] + (dt->mth == 1 && IS_LEAP_YEAR(dt->year))) * DAY)
		return (0);
	*n -= (g_ms[dt->mth] + (dt->mth == 1 && IS_LEAP_YEAR(dt->year))) * DAY;
	if (dt->mth == 0 && (dt->mth = 11))
		--dt->year;
	else
		--dt->mth;
	return (1);
}

int			ft_upd_day(t_date *dt, long int *n)
{
	if ((*n < DAY && *n >= 0) || (*n > -1 * DAY && *n < 0))
		return (0);
	if (*n > 0)
	{
		*n -= DAY;
		if (dt->day == g_ms[dt->mth] +
				(dt->mth == 1 && IS_LEAP_YEAR(dt->year)) && (dt->day = 1))
			if (dt->mth == 11 && !(dt->mth = 0))
				++dt->year;
			else
				++dt->mth;
		else
			++dt->day;
		return (1);
	}
	*n += DAY;
	if (dt->day == 1 && (dt->day = g_ms[dt->mth] +
			(dt->mth == 1 && IS_LEAP_YEAR(dt->year))))
		if (dt->mth == 0 && (dt->mth = 11))
			--dt->year;
		else
			--dt->mth;
	else
		--dt->day;
	return (1);
}

int			ft_add_hour(t_date *dt, long int *n)
{
	if (*n < 3600)
		return (0);
	*n -= 3600;
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
	return (1);
}

t_date		*ft_unix_time_to_date(long int ut)
{
	t_date *dt;

	if (!(dt = (t_date*)malloc(sizeof(t_date))))
		return (0);
	*dt = (t_date){1970, 0, 1, UTC, 0, 0};
	WHILE_TRUE(ft_upd_year(dt, &ut));
	WHILE_TRUE(ft_upd_month(dt, &ut));
	WHILE_TRUE(ft_upd_day(dt, &ut));
	WHILE_TRUE(ut >= 0 ? ft_add_hour(dt, &ut) : ft_sub_hour(dt, &ut));
	WHILE_TRUE(ut >= 0 ? ft_add_minute(dt, &ut) : ft_sub_minute(dt, &ut));
	WHILE_TRUE(ut >= 0 ? ft_add_second(dt, &ut) : ft_sub_second(dt, &ut));
	return (dt);
}
