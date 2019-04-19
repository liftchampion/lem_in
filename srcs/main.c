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

#include "len_in.h"

t_data 	*ft_parsing(int ac, char **av)
{
	t_data	*dt;
	t_pars	*prs;
	int		fd;

	if (!(prs = ft_parse_flags(ac, av)))
		return (0);
	fd = prs->input_file ? open(prs->input_file, O_RDONLY) : 0;
	if (!(dt = ft_parser(fd, prs)))
		return ((void*)(size_t)(ft_printf("Error\n") * 0));
	if (fd)
		close(fd);
	return (dt);
}

int		main(int ac, char **av)
{
	t_data	*dt;

	if (!(dt = ft_parsing(ac, av)))
		return (ft_free_data(dt, 0));

	if (!ft_find_all_flows(dt))
		return (0);

	//ft_print_flows(dt, 2);

	ft_fill_ants(dt);
	ft_print_murashi(dt);

	ft_print_string(dt->output);

	//ft_print_ants(dt);

	return (ft_free_data(dt, 0)); // todo close file if it was opened
}