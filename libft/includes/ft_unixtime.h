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

#ifndef FT_UNIXTIME_H
# define FT_UNIXTIME_H

# define DAY 86400
# define UTC 3
# define HALF_YEAR (31556926 / 2)
# define IS_LEAP_YEAR(y) ((!((y) % 400) || (!((y) % 4) && (y) % 100)) ? 1 : 0)

# define WHILE_TRUE(a) while(a)

typedef struct	s_date
{
	int			year;
	int			mth;
	char		day;
	char		hr;
	char		min;
	char		sec;
}				t_date;

t_date			*ft_unix_time_to_date(long int ut);
int				ft_upd_year(t_date *dt, long int *n);
int				ft_upd_month(t_date *dt, long int *n);
int				ft_upd_day(t_date *dt, long int *n);
int				ft_add_hour(t_date *dt, long int *n);
int				ft_sub_hour(t_date *dt, long int *n);
int				ft_add_minute(t_date *dt, long int *n);
int				ft_sub_minute(t_date *dt, long int *n);
int				ft_add_second(t_date *dt, long int *n);
int				ft_sub_second(t_date *dt, long int *n);

#endif
