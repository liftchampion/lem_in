/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mlx_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggerardy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/20 05:07:56 by ggerardy          #+#    #+#             */
/*   Updated: 2019/04/20 05:07:56 by ggerardy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include "libft.h"

void	ft_assign_mlx_data(t_mlx *mlx, int x, int y,
		t_mlx_init *init_data)
{
	mlx->x = x;
	mlx->y = y;
	mlx->bits_per_pixel = 32;
	mlx->size_line = x * (mlx->bits_per_pixel / 8);
	mlx->endian = 0;
	mlx->to_free_data = init_data->to_free_data;
	mlx->free_func = init_data->free_func;
	mlx->key_func = init_data->key_func;
	mlx->mouse_func = init_data->mouse_func;
	mlx->expose_func = init_data->expose_func;
	mlx->loop_func = init_data->loop_func;
	mlx->add_data = init_data->add_data;
}

t_mlx 	*ft_mlx_init(int x, int y, char *name,
		t_mlx_init tofree_data_freefunc_key_mouse_expose_loop)
{
	t_mlx *mlx;

	if (!(mlx = ft_memalloc(sizeof(t_mlx))))
		return (ft_destroy_mlx(mlx, 0));
	ft_assign_mlx_data(mlx, x, y,
			&tofree_data_freefunc_key_mouse_expose_loop);
	if (!(mlx->mlx_ptr = mlx_init()))
		return (ft_destroy_mlx(mlx, 0));
	if (!(mlx->win_ptr = mlx_new_window(mlx->mlx_ptr, x, y, name)))
		return (ft_destroy_mlx(mlx, 0));
	if (!(mlx->img = mlx_new_image(mlx->mlx_ptr, x, y)))
		return (ft_destroy_mlx(mlx, 0));
	if (!(mlx->img_data = (int*)mlx_get_data_addr(mlx->img,
			&mlx->bits_per_pixel, &mlx->size_line, &mlx->endian)))
		return (ft_destroy_mlx(mlx, 0));
	ft_bzero(mlx->img_data, sizeof(char) * x * y * (mlx->bits_per_pixel / 8));
	mlx_hook(mlx->win_ptr, 17, 0, ft_mlx_close, mlx);
	mlx_key_hook(mlx->win_ptr, ft_mlx_main_key_hook, mlx);
	mlx_mouse_hook(mlx->win_ptr, ft_mlx_main_mouse_hook, mlx);
	mlx_expose_hook(mlx->win_ptr, ft_mlx_main_expose_hook, mlx);
	mlx_loop_hook(mlx->mlx_ptr, ft_mlx_main_loop_hook, mlx);
	return (mlx);
}
