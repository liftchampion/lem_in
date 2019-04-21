/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggerardy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 19:50:42 by ggerardy          #+#    #+#             */
/*   Updated: 2019/04/08 22:10:45 by ggerardy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "len_in.h"
#include "lem_in_structs.h"

static inline void	ft_inl_swap(void **x, void **y)
{
	void *h;

	h = *x;
	*x = *y;
	*y = h;
}

void		ft_upd_pts(t_data *dt)
{
	int i;
	int len;
	int *p;
	int dst;

	len = dt->nodes->len;
	i = -1;
	while (++i < len)
	{
		p = &((t_node*)dt->nodes->data[i])->p;
		dst = dt->dsts[i];
		if (*p == INF || dst == INF)
			*p = INF;
		else
			*p += dst;
	}
}

void		ft_sort_paths_in_flow(t_data *dt, int flow)
{
	size_t j;
	size_t k;
	t_vector *curr_flow;

	curr_flow = dt->flows->data[flow];
	j = (size_t)-1;
	while (++j < curr_flow->len)
	{
		k = j - 1;
		while (++k < curr_flow->len)
		{
			if (((t_vector*)curr_flow->data[k])->len <
					((t_vector*)curr_flow->data[j])->len)
				ft_inl_swap(curr_flow->data + j, curr_flow->data + k);
		}
	}
}

void		ft_print_flows(t_data *dt, int mode)
{
	t_vector *flows;
	t_vector *curr_flow;
	t_vector *curr_path;

	flows = dt->flows;

	ft_printf("Flows count: %d\n", (int)flows->len);
	for (size_t i = 0; i < flows->len; ++i)
	{
		ft_printf("~~~~~~~~~~~~~~~~~~~~~~ %2d ~~~~~~~~~~~~~~~~~~~~~~\n", i + 1);
		curr_flow = flows->data[i];
		for (size_t j = 0; j < curr_flow->len; ++j)
		{
			ft_printf("%2d: ", j + 1);
			curr_path = curr_flow->data[j];
			if (mode == 1)
			{
				for (size_t k = 0; k < curr_path->len; ++k)
				{
					int idx = (int)curr_path->data[k];
					ft_printf("%s ", ((t_node *)dt->nodes->data[idx])->name);
				}
				ft_printf("\n");
			}
			if (mode == 2)
			{
				ft_printf("%d({Yellow}%d{eof})\n",
						(int)curr_path->len,
						curr_path->offset);
			}
		}
		ft_printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	}
}

int 		ft_find_min_w(void **chs, int len, int next)
{
	int min_w = INF;
	int i;

	i = -1;
	while (++i < len)
	{
		int w = GET_W(chs[i]);
		int idx = GET_I(chs[i]);
		if (idx == next)
		{
			if (w < min_w)
				min_w = w;
		}
	}
	return (min_w);
}

int 		ft_find_path_len(t_data *dt)
{
	void	**path;
	int		len;
	int		i;
	int 	path_len;

	path_len = 0;
	path = dt->path->data;
	len = dt->path->len;
	i = len;

	while (--i > 0)
	{
		int curr_node;
		int next_node;
		int w;
		curr_node = (int)path[i];
		next_node = (int)path[i - 1];
		w = ft_find_min_w(((t_node*)dt->nodes->data[curr_node])->chs->data,
				((t_node*)dt->nodes->data[curr_node])->chs->len, next_node);
		path_len += w + ((t_node*)dt->nodes->data[curr_node])->p -
				((t_node*)dt->nodes->data[next_node])->p;
	}
	return (path_len);
}

void 		ft_print_path_to_file(t_data *dt)
{
	void	**path;
	int		len;
	int		i;
	int		fd;

	fd = open("path.my.test", O_TRUNC | O_WRONLY);
	path = dt->path->data;
	len = dt->path->len;
	i = len;

	int path_len = ft_find_path_len(dt);

	ft_fdprintf(fd, "Len: %d\n", path_len);
	ft_printf("Len: %d\n", path_len);
	while (--i >= 0)
	{
		ft_fdprintf(fd, "%d\n", (int)path[i]);
	}
	close(fd);
}

void 		ft_printf_graph_to_file(t_data *dt)
{
	t_node **nodes;
	int nodes_count;
	int i;
	int fd;

	fd = open("graph.test", O_TRUNC | O_WRONLY);
	nodes = (t_node**)dt->nodes->data;
	nodes_count = dt->nodes->len;
	i = -1;
	ft_fdprintf(fd, "%d %d\n", dt->start, dt->end);
	while (++i < nodes_count)
	{
		int j = -1;
		void **chs = (void**)nodes[i]->chs->data;
		int len = nodes[i]->chs->len;
		while (++j < len)
		{
			ft_fdprintf(fd, "%d %d %d\n", i, GET_I(chs[j]),
					GET_W(chs[j]) + nodes[i]->p - nodes[GET_I(chs[j])]->p);
		}
	}
	close(fd);
}

void		ft_call_python_and_compare_paths()
{
	system("cat graph.test | ./main.py");
	system("diff path.my.test path.ref.test | wc -l |"
		"awk '{print \"\\x1B[38;5;202m\" $1 \"\\x1B[0m\"}'");
	//sleep(2);
}