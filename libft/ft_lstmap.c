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

#include "libft.h"
#include <stdlib.h>

static void	ft_free_list(t_list *lst)
{
	t_list *tmp;

	if (!lst)
		return ;
	while (lst)
	{
		tmp = lst;
		if (lst->content)
		{
			free(lst->content);
		}
		free(lst);
		lst = tmp->next;
	}
}

t_list		*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list *new_ptr;
	t_list *tmp;
	t_list *ret;

	if (!lst || !f)
		return (0);
	tmp = 0;
	ret = 0;
	while (lst)
	{
		new_ptr = f(lst);
		if (tmp == 0)
			ret = new_ptr;
		else
		{
			tmp->next = new_ptr;
			if (tmp->next == 0)
			{
				ft_free_list(ret);
			}
		}
		tmp = new_ptr;
		lst = lst->next;
	}
	return (ret);
}
