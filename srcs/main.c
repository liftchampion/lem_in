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
#include "len_in.h"

int		main(void)
{
	t_data *dt;

	//int fd = 0;
	int fd = open("big.test", O_RDONLY);
	if (!(dt = ft_parser(fd)))
		return (ft_printf("Error\n") * 0);
	for (int i = 0; i < 1000; ++i)
	{
		dijkstra(dt);
		ft_upd_pts(dt);
		ft_find_shortest_path(dt);
	}
	//ft_print_parsed(dt);
	//ft_print_dijkstra(dt, 2);

	ft_print_path(dt, 3);
	return (ft_free_data(dt, 0));
}