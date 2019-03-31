/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shapka.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggerardy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 17:25:22 by ggerardy          #+#    #+#             */
/*   Updated: 2019/03/15 00:55:37 by ggerardy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strrchr(const char *str, int ch)
{
	unsigned char	c;
	char			*ret;

	ret = 0;
	c = (unsigned char)ch;
	while (*str)
	{
		if (*str == c)
		{
			ret = (char*)str;
		}
		str++;
	}
	if (*str == 0 && c == 0)
		ret = (char*)str;
	return (ret);
}
