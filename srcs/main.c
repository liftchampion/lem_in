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

int 	ft_processing(t_data *dt)
{
	int			partitial_case;
	t_vector	*first_path;

	if (!(partitial_case = ft_procede_partitial_case(dt)))
		return (0);
	if (partitial_case == 1 || partitial_case == 2)
		return (1);
	if (!ft_find_all_flows(dt))
		return (0);
	if (GET_FLOWS(dt->prs->flags))
		ft_print_flows(dt);
	if (GET_FAST(dt->prs->flags))
	{
		first_path =
			((t_vector*)((t_vector*)dt->flows->data[dt->best_flow])->data[0]);
		dt->turns = first_path->offset + first_path->len - 1;
		return (1);
	}
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
	if (dt->output)
		ft_print_string(dt->output);
	if (GET_FMT_M(dt->prs->flags))
		ft_printf("%d\n", dt->turns);
	if (GET_VIS(dt->prs->flags))
	{
		dt->screen_h = 1080;
		dt->screen_w = 1920;
		if (ft_get_dims(dt) <= 0)
			return (ft_free_data(dt, 0) * ft_printf("Dimensions Error\n"));
		ft_printf("%d %d %d %d %d %d\n", dt->dims->side, dt->dims->lines_count,
				dt->dims->gap, dt->dims->h_pad, dt->dims->v_pad, dt->dims->line_len);
		if (!(dt->mlx = ft_mlx_init(1920, 1080, "Super Muravii",
				(t_mlx_init){dt, dt, ft_free_for_mlx, 0, 0, ft_mlx_expose, 0})))
			return (ft_printf("MLX Error\n") * 0);
		mlx_loop(dt->mlx->mlx_ptr);
	}

	return (ft_free_data(dt, 0));
}
