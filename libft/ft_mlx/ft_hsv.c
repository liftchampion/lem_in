/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hsv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggerardy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 10:32:47 by ggerardy          #+#    #+#             */
/*   Updated: 2019/04/22 10:32:47 by ggerardy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_mlx.h"

static inline void	ft_find_maxmin(const unsigned char rgb[3],
		unsigned char maxmin[2])
{
	unsigned char max;
	unsigned char min;

	max = rgb[0];
	max = rgb[1] > max ? rgb[1] : max;
	max = rgb[2] > max ? rgb[2] : max;

	min = rgb[0];
	min = rgb[1] < min ? rgb[1] : min;
	min = rgb[2] < min ? rgb[2] : min;
	maxmin[0] = max;
	maxmin[1] = min;
}

t_hsv	ft_rgb_to_hsv(unsigned int argb)
{
	unsigned char	rgb[3];
	unsigned char	maxmin[2];
	double			delta;
	t_hsv			hsv;

	rgb[0] = (unsigned char)((double)((argb & 0x00FF0000u) >> 16u));
	rgb[1] = (unsigned char)((double)((argb & 0x0000FF00u) >> 8u));
	rgb[2] = (unsigned char)((double)(argb & 0x000000FFu));
	ft_find_maxmin(rgb, maxmin);
	delta = maxmin[0] - maxmin[1];
	hsv.vol = (unsigned char)(maxmin[0] * (100. / 255) + 0.5);
	hsv.sat = !maxmin[0] ? 0 : (unsigned char)(delta * 100 / (maxmin[0]) + 0.5);
	if (maxmin[0] == maxmin[1])
		hsv.hue = 0;
	else if (maxmin[0] == rgb[0])
		hsv.hue = (unsigned short)(60 * ((rgb[1] - rgb[2]) / delta) +
				(rgb[1] < rgb[2]) * 360 + 0.5);
	else if (maxmin[0] == rgb[1])
		hsv.hue = (unsigned short)(60 * ((rgb[2] - rgb[0]) / delta + 2) + 0.5);
	else if (maxmin[0] == rgb[2])
		hsv.hue = (unsigned short)(60 * ((rgb[0] - rgb[1]) / delta + 4) + 0.5);
	return (hsv);
}