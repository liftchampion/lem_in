/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vis.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggerardy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/20 01:27:29 by ggerardy          #+#    #+#             */
/*   Updated: 2019/04/20 01:27:29 by ggerardy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "len_in.h"

#ifndef NO_VISUALIZATION

unsigned int		ft_get_color(t_data *dt, int i)
{
	unsigned int res;

	if (dt->sorted_nodes[i].name == dt->start)
		return (START_COLOR);
	else if (dt->sorted_nodes[i].name == dt->end - 1)
		return (END_COLOR);
	else if (dt->sorted_nodes[i].dst != INF)
		res = ft_hsv_gradient(GRAD_START, GRAD_END,
			(double[3]){0, dt->sorted_nodes[i].dst, dt->max_dst}, GRAD_DIR);
	else
		res = UNREACHING_NODES_COLOR;
	return (res);
}

int					ft_lemin_keyhook(int key, void *p)
{
	t_mlx *mlx;

	mlx = p;
	if (key == KEY_RIGHT || key == KEY_LEFT)
		ft_turn(mlx->add_data, key == KEY_RIGHT ? 1 : -1);
	ft_print_map(p);
	ft_draw_ants(mlx->add_data);
	ft_mlx_put_img(mlx);
	ft_print_texts(p);
	return (0);
}

int					ft_mlx_expose(void *p)
{
	t_mlx *mlx;

	mlx = p;
	ft_mlx_rectput(mlx, (t_point){mlx->x, mlx->y}, (t_point){0, 0}, GRAY);
	ft_print_map(p);
	ft_draw_ants(mlx->add_data);
	ft_mlx_put_img(mlx);
	ft_print_texts(p);
	return (0);
}

int					ft_visualize(t_data *dt)
{
	dt->screen_h = 1080;
	dt->screen_w = 2400;
	if (ft_get_dims(dt) <= 0)
		return (ft_free_data(dt, 0) * ft_printf("Vis: Map is too big!\n"));
	if (!ft_vis_init_ants(dt))
		return (ft_free_data(dt, 0) * ft_printf("Vis: Ants managing Error\n"));
	ft_rm_lines_from_output(dt);
	if (dt->output)
		ft_print_string(dt->output);
	ft_printf(!GET_FMT_M(dt->prs->flags) ? "\n" : "");
	if (!(dt->mlx = ft_mlx_init(dt->screen_w, dt->screen_h, "Super Muravii",
			(t_mlx_init)
			{dt, dt, ft_free_for_mlx, ft_lemin_keyhook, 0, ft_mlx_expose, 0})))
		return (ft_printf("Vis: MLX Error\n") * 0);
	mlx_loop(dt->mlx->mlx_ptr);
	return (1);
}

#else

int					ft_visualize(t_data *dt)
{
	if (dt->output)
		ft_print_string(dt->output);
	ft_printf("Visualisation is {Red}disabled{eof}!\n");
	return (1);
}

#endif
