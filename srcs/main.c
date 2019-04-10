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

	if (!(dt = ft_parser()))
		return (ft_printf("Error\n") * 0);
	//ft_print_parsed(dt);
	dijkstra(dt);
	ft_print_dijkstra(dt);
	return (ft_free_data(dt, 0));
}