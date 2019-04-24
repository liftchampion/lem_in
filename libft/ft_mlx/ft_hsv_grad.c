/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hsv_grad.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggerardy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 13:18:12 by ggerardy          #+#    #+#             */
/*   Updated: 2019/04/22 13:18:12 by ggerardy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_mlx.h"

unsigned int	ft_hsv_gradient(t_hsv from, t_hsv to,
		const double points[3], char dir)
{
	t_hsv	res;
	double	relate;
	double	dst;

	relate = (points[1] - points[0]) / (points[2] - points[0]);
	if (dir == 1)
		res.hue =
			(unsigned short)(from.hue + ((to.hue - from.hue) * relate)) % 360;
	if (dir == -1)
	{
		dst = from.hue + 360 - to.hue;
		res.hue = (360 + (short)(from.hue - (dst * relate))) % 360;
	}
	res.vol = (unsigned char)(from.vol + ((to.vol - from.vol) * relate));
	res.sat = (unsigned char)(from.sat + ((to.sat - from.sat) * relate));
	return (ft_hsv_to_rgb(res));
}
