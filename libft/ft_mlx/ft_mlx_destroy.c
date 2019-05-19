/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mlx_destroy.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggerardy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/20 05:08:44 by ggerardy          #+#    #+#             */
/*   Updated: 2019/05/19 21:18:47 by ggerardy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include "libft.h"

void		*ft_destroy_mlx(t_mlx *mlx, int ret)
{
	if (!mlx)
		return ((void*)(size_t)ret);
	if (mlx->img)
		mlx_destroy_image(mlx->mlx_ptr, mlx->img);
	if (mlx->win_ptr)
		mlx_destroy_window(mlx->mlx_ptr, mlx->win_ptr);
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
