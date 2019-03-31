/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shapka                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggerardy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 17:25:22 by ggerardy          #+#    #+#             */
/*   Updated: 2019/03/15 00:55:37 by ggerardy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "libft.h"
#include "ft_get_next_line.h"

int				ft_gnl_free_ret(t_string *str, int ret)
{
	free(str);
	return (ret);
}

int				ft_get_next_line(const int fd, char **line, int buff_size)
{
	static t_map	*fd_bf = 0;
	t_result		res;
	t_buf			**curr_buf;
	t_string		*str;

	str = 0;
	res = !line ? ERROR : ft_gnl_init_works(fd, &fd_bf, &curr_buf, buff_size);
	if (res != ERROR)
		res = ft_get_line_from_buffer(*curr_buf, &str, fd);
	if (res == ENDL_NOT_FOUND)
		res = ft_append_line(*curr_buf, fd, str);
	if (res == ERROR || !ft_string_fit(&str))
		res = ERROR;
	if (res != ERROR && line)
		*line = (str == 0) ? *line : str->data;
	else if (line)
		*line = 0;
	if (res == NO_LINE || res == ERROR ||
		(fd >= 0 && fd <= 2 && (*curr_buf)->pos == (*curr_buf)->len))
	{
		ft_map_del(fd_bf, (void*)(size_t)fd);
		if (fd_bf && fd_bf->size == 0)
			ft_free_map(&fd_bf);
	}
	return (ft_gnl_free_ret(str, res));
}
