/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_color.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehugh-be <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/23 13:47:48 by ehugh-be          #+#    #+#             */
/*   Updated: 2019/03/15 00:55:37 by ggerardy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "ft_color.h"

static int	ft_check_str(const char **frmt)
{
	int i;
	int j;

	i = -1;
	while (++i < NUM_OF_COLS && (j = -1))
	{
		while (j++ || 1)
			if (!pf_cols[i].name[j] || (*frmt)[j] != pf_cols[i].name[j])
				break ;
		if (!pf_cols[i].name[j])
			break ;
	}
	*frmt += j;
	return (i);
}

static int	ft_parse_format(const char **frm, t_string **str)
{
	char	bgre;
	int		i;
	char	buf[20];

	bgre = 0;
	bgre += (*(*frm) == 'b' && *(*frm + 1) == '_') ? 10 : 0;
	bgre += (*(*frm) == 'r' && *(*frm + 1) == '_') ? 1 : 0;
	*frm += (*(*frm) == 'b' || *(*frm) == 'r') && *(*frm + 1) == '_' ? 2 : 0;
	i = ft_check_str(frm);
	if (i == NUM_OF_COLS)
		return ((ft_string_push_back_s(str, "0m") < 1) ? -1 : 0);
	bgre -= (pf_cols[i].num < 10 && bgre / 10 == 1) ? 10 : 0;
	bgre -= (pf_cols[i].num > 10 && bgre % 10 == 1) ? 1 : 0;
	bgre = (pf_cols[i].num == 0) ? (char)0 : bgre;
	return ((ft_string_push_back_s(str, ft_itoa_buf(pf_cols[i].num + bgre +
						bgre % 10 * 20, buf)) < 1) ? -1 : 1);
}

static int	ft_parse_compl_col(const char **frmt, t_string **str)
{
	if (*(++(*frmt)) == 'b' && *(*frmt + 1) == '_')
	{
		*frmt += 2;
		if (!ft_string_push_back_s(str, "48;5;"))
			return (-1);
	}
	else if (!ft_string_push_back_s(str, "38;5;"))
		return (-1);
	while (ft_isdigit(**frmt))
		if (ft_string_push_back(str, *((*frmt)++)) < 1)
			return (-1);
	return (1);
}

static int	ft_loop(const char **frmt, t_string **str)
{
	int ret;

	while (**frmt && **frmt != '}')
	{
		if (*(*frmt) == '\\')
		{
			if (ft_parse_compl_col(frmt, str) < 1)
				return (-1);
		}
		else if ((ret = ft_parse_format(frmt, str)) < 1)
			return (ret);
		if (**frmt != ',')
		{
			if (**frmt != '}')
			{
				(*str)->len--;
				(*str)->data[(*str)->len] = '\0';
			}
			break ;
		}
		else if (!(*frmt)++ || !ft_string_push_back(str, ';'))
			return (-1);
	}
	return (0);
}

int			ft_set_color(const char **frmt, t_string **str)
{
	int ret;

	if (!frmt || !*frmt || !str || !*str)
		return (-1);
	ft_string_push_back_s(str, FT_COL_PREFIX);
	if ((ret = ft_loop(frmt, str)))
		return (ret);
	while (**frmt && **frmt != '}')
		(*frmt)++;
	ft_string_push_back_s(str, "m");
	return (0);
}
