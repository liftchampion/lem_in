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

static inline void	ft_rgb_filler_1(unsigned char rgb[3], const double vdmi[4],
		unsigned char hi)
{
	const double v = vdmi[0];
	const double d = vdmi[1];
	const double m = vdmi[2];
	const double i = vdmi[3];

	if (hi == 0)
	{
		rgb[0] = (unsigned char)(v * (255 / 100.) + 0.5);
		rgb[1] = (unsigned char)(i * (255 / 100.) + 0.5);
		rgb[2] = (unsigned char)(m * (255 / 100.) + 0.5);
	}
	else if (hi == 1)
	{
		rgb[0] = (unsigned char)(d * (255 / 100.) + 0.5);
		rgb[1] = (unsigned char)(v * (255 / 100.) + 0.5);
		rgb[2] = (unsigned char)(m * (255 / 100.) + 0.5);
	}
	else if (hi == 2)
	{
		rgb[0] = (unsigned char)(m * (255 / 100.) + 0.5);
		rgb[1] = (unsigned char)(v * (255 / 100.) + 0.5);
		rgb[2] = (unsigned char)(i * (255 / 100.) + 0.5);
	}
}

static inline void	ft_rgb_filler_2(unsigned char rgb[3], const double vdmi[4],
		unsigned char hi)
{
	const double v = vdmi[0];
	const double d = vdmi[1];
	const double m = vdmi[2];
	const double i = vdmi[3];

	if (hi == 3)
	{
		rgb[0] = (unsigned char)(m * (255 / 100.) + 0.5);
		rgb[1] = (unsigned char)(d * (255 / 100.) + 0.5);
		rgb[2] = (unsigned char)(v * (255 / 100.) + 0.5);
	}
	else if (hi == 4)
	{
		rgb[0] = (unsigned char)(i * (255 / 100.) + 0.5);
		rgb[1] = (unsigned char)(m * (255 / 100.) + 0.5);
		rgb[2] = (unsigned char)(v * (255 / 100.) + 0.5);
	}
	else if (hi == 5)
	{
		rgb[0] = (unsigned char)(v * (255 / 100.) + 0.5);
		rgb[1] = (unsigned char)(m * (255 / 100.) + 0.5);
		rgb[2] = (unsigned char)(d * (255 / 100.) + 0.5);
	}
}

unsigned int	ft_hsv_to_rgb(t_hsv hsv)
{
	unsigned char	rgb[3];
	unsigned int	res;
	unsigned char hi;
	double v_min;
	double a;
	double v_inc;
	double v_dec;

	hi = (int)(hsv.hue / 60.) % 6;
	v_min = ((100 - hsv.sat) * hsv.vol) / 100.;
	a = (hsv.vol - v_min) * ((hsv.hue % 60) / 60.);
	v_inc = v_min + a;
	v_dec = hsv.vol - a;
	if (hi < 3)
		ft_rgb_filler_1(rgb,
				(double[4]){(double)hsv.vol, v_dec, v_min, v_inc}, hi);
	else
		ft_rgb_filler_2(rgb,
				(double[4]){(double)hsv.vol, v_dec, v_min, v_inc}, hi);
	res = 0;
	res |= (unsigned)((unsigned)rgb[0] << 16u);
	res |= (unsigned)((unsigned)rgb[1] << 8u);
	res |= (unsigned)rgb[2];
	return (res);
}
