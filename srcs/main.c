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
	if (prs->ant_names && !ft_parse_ants_names(dt))
		return
		((void*)(size_t)(ft_printf("Error during parsing ants' names\n") * 0));
	return (dt);
}

int 	ft_print_murashi_simple(t_data *dt)
{
	int i;
	char *tmp_line;
	char *end_name;

	i = -1;
	end_name = ((t_node*)dt->nodes->data[dt->end - 1])->name;
	while (++i < dt->ant_count)
	{
		if (dt->prs->ant_names)
			ft_sprintf(&tmp_line, "L%s-%s ", dt->ant_names->data[i], end_name);
		else
			ft_sprintf(&tmp_line, "L%d-%s ", i + 1, end_name);
		if (!tmp_line)
			return (0);
		if (!ft_string_push_back_s(&dt->output, tmp_line))
			return (free_ret(tmp_line, 0));
		free(tmp_line);
	}
	if (!ft_string_push_back(&dt->output, '\n'))
		return (0);
	dt->turns = 1;
	return (1);
}

int 	ft_procede_partitial_case(t_data *dt)
{
	int		i;
	void	**start_children;
	int		end;
	int 	len;

	if (dt->start == dt->end)
		return (1);
	i = -1;
	start_children = ((t_node*)dt->nodes->data[dt->start])->chs->data;
	len = ((t_node*)dt->nodes->data[dt->start])->chs->len;
	end = dt->end;
	while (++i < len)
	{
		if (GET_I(start_children[i]) == end)
			if (!ft_print_murashi_simple(dt))
				return (0);
	}
	return (dt->turns == 1 ? 2 : -1);
}

int 	ft_processing(t_data *dt)
{
	int partitial_case;

	if (!(partitial_case = ft_procede_partitial_case(dt)))
		return (0);
	if (partitial_case == 1 || partitial_case == 2)
		return (1);
	if (!ft_find_all_flows(dt))
		return (0);
	if (!ft_fill_ants(dt))
		return (0);
	if (!ft_print_murashi(dt))
		return (0);
	return (1);
}

int		main(int ac, char **av)
{
	t_data	*dt;

	if (!(dt = ft_parsing(ac, av)))
		return (ft_free_data(dt, 0));
	if (!ft_processing(dt))
		return (ft_free_data(dt, 0) * ft_printf("Error\n"));
	ft_print_string(dt->output);

	return (ft_free_data(dt, 0)); // todo close file if it was opened
}