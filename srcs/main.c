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

int		main(void)
{
	t_data *dt;

	int fd = 0;
	//int fd = open("big.test", O_RDONLY);
	if (!(dt = ft_parser(fd)))
		return (ft_printf("Error\n") * 0);

	//ft_print_parsed(dt);

	if (!ft_find_all_flows(dt))
		return (0);
	//ft_printf("{Red}Flows count: %d{eof}\n", dt->max_flow);

	/*for (size_t i = 0; i < dt->nodes->len; ++i)
	{
		tt u;
		u.ui = dt->nd_to_flow[i];
		ft_printf("%-10s: %#llB\n", ((t_node*)dt->nodes->data[i])->name, u.ll[1]);
	}*/

	ft_sort_flows(dt);
	//if (!ft_make_flows(dt, dt->max_flow))
	//	return (0);
	//ft_printf("Done!\n");
	ft_send_lems(dt);
	//ft_print_flows(dt, 2);

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

	u.ui |= (__uint128_t)-1 >> 10u;
	//u.ui |= (__uint128_t)-1 >> 1u;
	//u.ui |= (__uint128_t)-1 >> 2u;


	//u.ui &= ~((__uint128_t)-1 >> 3u);
	//u.ui |= (__uint128_t)-1 >> 4u;


	//if (& ((__uint128_t)1 >> (unsigned)flow))

	ft_printf("%#llB\n%#llB\n", u.ll[1], u.ll[0]);*/
	//test |= (__uint128_t)1 << 127u;
	//test |= (__uint128_t)1 << 0u;



	//ft_print_parsed(dt);
	//ft_print_dijkstra(dt, 2);

	//ft_print_path(dt, 3);
	//return (ft_free_data(dt, 0));
	return (ft_free_data(dt, 0));
}