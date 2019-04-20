/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mlx_hooks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggerardy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/20 05:05:19 by ggerardy          #+#    #+#             */
/*   Updated: 2019/04/20 05:05:19 by ggerardy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include "libft.h"
#include "ft_mlx.h"

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
