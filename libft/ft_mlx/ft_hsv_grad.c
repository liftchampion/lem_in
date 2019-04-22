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

unsigned int	ft_hsv_gradient(t_hsv from, t_hsv to, double points[3], char dir)
{
	t_hsv res;
	double relate;

	static int prev = -1;

	dir = 0;
	relate = (points[1] - points[0]) / (points[2] - points[0]);
	res.hue = (unsigned short)(from.hue + ((to.hue - from.hue) * relate));
	res.vol = (unsigned char)(from.vol + ((to.vol - from.vol) * relate));
	res.sat = (unsigned char)(from.sat + ((to.sat - from.sat) * relate));

	if (res.hue != prev)
		ft_printf("%hu %#.8X\n", res.hue, ft_hsv_to_rgb(res));
	prev = res.hue;

	return (ft_hsv_to_rgb(res));
}