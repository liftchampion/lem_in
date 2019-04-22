/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mlx_img.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggerardy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/20 05:09:22 by ggerardy          #+#    #+#             */
/*   Updated: 2019/04/20 05:09:22 by ggerardy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include "libft.h"

void	ft_mlx_rectput(t_mlx *mlx, t_point size, t_point pos, int color)
{
	int x;
	int y;

	if (size.x <= 0 || size.y <= 0)
		return ;
	y = pos.y;
	while (y < pos.y + size.y)
	{
		x = pos.x;
		while (x < pos.x + size.x)
		{
			ft_mlx_pixelput(mlx, x, y, color);
			++x;
		}
		++y;
	}
}

void	ft_mlx_frameput(t_mlx *mlx, t_point size, t_point pos, int color)
{
	int x;
	int y;

	if (size.x <= 0 || size.y <= 0)
		return ;
	y = pos.y - 1;
	while (++y < pos.y + size.y)
	{
		ft_mlx_pixelput(mlx, pos.x, y, color);
		ft_mlx_pixelput(mlx, pos.x + size.x - 1, y, color);
	}
	x = pos.x - 1;
	while (++x < pos.x + size.x)
	{
		ft_mlx_pixelput(mlx, x, pos.y, color);
		ft_mlx_pixelput(mlx, x, pos.y + size.y - 1, color);
	}
}

void 	ft_mlx_pixelput(t_mlx *mlx, int x, int y, int color)
{
	static int	max = -1;
	int			pos;

	if (max == -1)
		max = mlx->y * mlx->x;
	pos = y * mlx->x + x;
	if (pos < 0 || pos >= max)
		return ;
	mlx->img_data[pos] = color;
}

void 	ft_mlx_put_img(t_mlx *mlx)
{
	if (!mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->img, 0, 0))
		ft_mlx_close(mlx);
}

void 	ft_mlx_clear(t_mlx *mlx)
{
	ft_bzero(mlx->img_data, mlx->x * mlx->y);
	ft_mlx_put_img(mlx);
}
