/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flows.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggerardy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 06:36:11 by ggerardy          #+#    #+#             */
/*   Updated: 2019/04/11 06:36:11 by ggerardy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "len_in.h"


static inline void	ft_inl_swap(void **x, void **y)
{
	void *h;

	h = *x;
	*x = *y;
	*y = h;
}

static inline int	ft_find_min_weigth(void **v, int len, int to_find)
{
	int i;
	int res_w;
	int res_i;

	i = -1;
	res_w = INF;
	res_i = INF;
	while (++i < len)
	{
		if (GET_I(v[i]) == to_find && GET_W(v[i]) < res_w)
		{
			res_w = GET_W(v[i]);
			res_i = i;
		}
	}
	ft_inl_swap(v + res_i, v + len - 1);
	return (res_w);
}

static inline void	ft_rm_curr(void **v, void *to_del, int len)
{
	int i;
	int stop;

	i = 0;
	stop = 0;
	while (!stop)
	{
		if (v[i] == to_del)
		{
			ft_inl_swap(v + i, v + len - 1);
			stop = 1;
		}
		i++;
	}
}

int		ft_rm_link(int i1, int i2, t_data *dt)
{
	t_node	*n1;
	t_node	*n2;
	int		w;

	n1 = dt->nodes->data[i1];
	n2 = dt->nodes->data[i2];
	w = ft_find_min_weigth(n1->chs->data, n1->chs->len--, i2);
	if (!ft_vector_push_back(&n1->prs, TO_EDGE(i2, -w)))
		return (0);
	ft_rm_curr(n2->prs->data, TO_EDGE(i1, w), n2->prs->len--);
	if (!ft_vector_push_back(&n2->chs, TO_EDGE(i1, -w)))
		return (0);
	return (1);
}

int		ft_send_flow(t_data *dt)
{
	int i;
	int curr;
	int next;
	size_t *path;

	path = (size_t*)dt->path->data;
	i = dt->path->len;
	while (--i)
	{
		curr = path[i];
		next = path[i - 1];
		if (!ft_rm_link(curr, next, dt))
			return (0);
	}
	return (1);
}