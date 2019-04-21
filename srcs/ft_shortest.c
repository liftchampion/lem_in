/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_shortest.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggerardy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 03:58:40 by ggerardy          #+#    #+#             */
/*   Updated: 2019/04/11 03:58:40 by ggerardy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "len_in.h"

int		ft_find_shortest_path(t_data *dt)
{
	int curr_node;

	curr_node = dt->end;
	if (dt->dsts[curr_node] == INF)
		return (0);
	dt->path->len = 0;
	while (curr_node != dt->start)
	{
		ft_vector_push_back(&dt->path, (void*)(size_t)curr_node);
		curr_node = ((t_node*)dt->nodes->data[curr_node])->from;
	}
	ft_vector_push_back(&dt->path, (void*)(size_t)dt->start);


	ft_print_path_to_file(dt);
	ft_call_python_and_compare_paths();

	char *ln;
	int fd = open("path.ref.test", O_RDONLY);
	int len = dt->path->len;
	ft_get_next_line(fd, &ln, 1);
	while (ft_get_next_line(fd, &ln, 1))
	{
		int nd = ft_atoi(ln);
		dt->path->data[--len] = (void*)(size_t)nd;
	}
	close(fd);

	ft_printf("begin new\n");
	ft_print_path_to_file(dt);
	ft_call_python_and_compare_paths();
	ft_printf("end new\n");



	return (dt->path ? 1 : 0);
}
