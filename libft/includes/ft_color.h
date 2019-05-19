/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_color.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehugh-be <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/23 17:59:45 by ehugh-be          #+#    #+#             */
/*   Updated: 2019/03/15 00:55:37 by ggerardy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_COLOR_H
# define FT_COLOR_H
# define NUM_OF_COLS 24
# define FT_COL_PREFIX "\e["
# define FT_COL_PREFIXD "\\e["

struct	s_pf_col
{
	char	*name;
	int		num;
};

struct s_pf_col pf_cols[] =
{
	{ "eof", 0},
	{ "Bold", 1},
	{ "Dim", 2},
	{ "Underlined", 4},
	{ "Blink", 5},
	{ "Reverse", 7},
	{ "Hidden", 8},
	{ "Default", 39 },
	{ "Black", 30},
	{ "Red", 31},
	{ "Green", 32},
	{ "Yellow", 33},
	{ "Blue", 34},
	{ "Magenta", 35},
	{ "Cyan", 36},
	{ "Light gray", 37},
	{ "Dark gray", 90},
	{ "Light red", 91},
	{ "Light green", 92},
	{ "Light yellow", 93},
	{ "Light blue", 94},
	{ "Light magenta", 95},
	{ "Light cyan", 96},
	{ "White", 97}
};
#endif
