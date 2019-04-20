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

#include <mlx.h>
#include "libft.h"

#include "len_in.h"

void	*ft_destroy_mlx(t_mlx *mlx, int ret)
{
	if (!mlx)
		return ((void*)(size_t)ret);
	if (mlx->img)
		mlx_destroy_image(mlx->mlx_ptr, mlx->img);
	if (mlx->win_ptr)
		mlx_destroy_image(mlx->mlx_ptr, mlx->win_ptr);
	free(mlx);
	return ((void*)(size_t)ret);
}

int			ft_mlx_close(void *p)
{
	t_mlx *mlx;

	mlx = p;
	if (mlx->free_func)
		mlx->free_func(mlx->to_free_data);
	ft_destroy_mlx(mlx, 0);
	exit(0);
	return (0);
}

int 		ft_mlx_main_key_hook(int key, void *data)
{
	t_mlx	*mlx;
	int		esc;
	int		ret;

	esc = 53;
	if (key == esc)
		ft_mlx_close(data);
	mlx = data;
	ret = 0;
	if (mlx->key_func)
		ret = mlx->key_func(key, mlx);
	return (ret);
}

int			ft_mlx_main_mouse_hook(int button, int x, int y, void *param)
{
	t_mlx	*mlx;
	int 	ret;

	ret = 0;
	mlx = param;
	if (mlx->mouse_func)
		ret = mlx->mouse_func(button, x, y, param);
	return (ret);
}

int			ft_mlx_main_expose_hook(void *param)
{
	t_mlx	*mlx;
	int 	ret;

	ret = 0;
	mlx = param;
	if (mlx->expose_func)
		ret = mlx->expose_func(param);
	return (ret);
}

int			ft_mlx_main_loop_hook(void *param)
{
	t_mlx	*mlx;
	int 	ret;

	ret = 0;
	mlx = param;
	if (mlx->loop_func)
		ret = mlx->loop_func(param);
	return (ret);
}

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
		t_mlx_init to_free_and_free_func_and_key_mouse_expose_loop_data)
{
	t_mlx *mlx;

	if (!(mlx = ft_memalloc(sizeof(t_mlx))))
		return (ft_destroy_mlx(mlx, 0));
	ft_assign_mlx_data(mlx, x, y,
			&to_free_and_free_func_and_key_mouse_expose_loop_data);
	if (!(mlx->mlx_ptr = mlx_init()))
		return (ft_destroy_mlx(mlx, 0));
	if (!(mlx->win_ptr = mlx_new_window(mlx->mlx_ptr, x, y, name)))
		return (ft_destroy_mlx(mlx, 0));
	if (!(mlx->img = mlx_new_image(mlx->mlx_ptr, x, y)))
		return (ft_destroy_mlx(mlx, 0));
	if (!(mlx->img_data = mlx_get_data_addr(mlx->img, &mlx->bits_per_pixel,
			&mlx->size_line, &mlx->endian)))
		return (ft_destroy_mlx(mlx, 0));
	ft_bzero(mlx->img_data, sizeof(char) * x * y * (mlx->bits_per_pixel / 8));
	mlx_hook(mlx->win_ptr, 17, 0, ft_mlx_close, mlx);
	mlx_key_hook(mlx->win_ptr, ft_mlx_main_key_hook, mlx);
	mlx_mouse_hook(mlx->win_ptr, ft_mlx_main_mouse_hook, mlx);
	mlx_expose_hook(mlx->win_ptr, ft_mlx_main_expose_hook, mlx);
	mlx_loop_hook(mlx->mlx_ptr, ft_mlx_main_loop_hook, mlx);
	return (mlx);
}
