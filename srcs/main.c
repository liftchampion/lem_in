/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggerardy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/31 09:33:27 by ggerardy          #+#    #+#             */
/*   Updated: 2019/04/08 19:52:13 by ggerardy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <zconf.h>
#include "len_in.h"

typedef union
{
	__uint128_t ui;
	unsigned long long ll[2];
}	tt;

int		main(void)
{
	t_data *dt;

	//int fd = 0;
	int fd = open("4.test", O_RDONLY);
	if (!(dt = ft_parser(fd)))
		return (ft_printf("Error\n") * 0);
	if (!(dt->max_flow = ft_find_all_flows(dt)) ||
		!ft_make_flows(dt, dt->max_flow))
		return (0);

	/*for (int i = 0; i < 1000; ++i)
	{
		t_data *dt;
		int fd = open("tmp.test", O_RDONLY);
		if (!(dt = ft_parser(fd)))
			return (ft_printf("Error\n") * 0);


		//for (int i = 0; i < 1000; ++i)
		//	dijkstra(dt);
		//ft_print_parsed(dt);

		ft_find_all_flows(dt);
		ft_free_data(dt, 0);
		close(fd);
	}
	return (0);*/


	/*tt u;
	__uint128_t test = 0;
	u.ui = test;
	ft_printf("%#llB\n%#llB\n", u.ll[1], u.ll[0]);

	u.ui |= (__uint128_t)-1 >> 0u;
	u.ui |= (__uint128_t)-1 >> 1u;
	u.ui |= (__uint128_t)-1 >> 2u;


	u.ui &= ~((__uint128_t)-1 >> 3u);
	u.ui |= (__uint128_t)-1 >> 4u;

	ft_printf("%#llB\n%#llB\n", u.ll[1], u.ll[0]);*/
	//test |= (__uint128_t)1 << 127u;
	//test |= (__uint128_t)1 << 0u;



	//ft_print_parsed(dt);
	//ft_print_dijkstra(dt, 2);

	//ft_print_path(dt, 3);
	//return (ft_free_data(dt, 0));
	return (ft_free_data(dt, 0));
}