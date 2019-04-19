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
#include "libft.h"

void		*ft_realloc(void *old_data, size_t prev_size, size_t new_size)
{
	void	*new_data;
	size_t	i;

	if (!old_data)
		return (0);
	new_data = ft_memalloc(new_size);
	if (!new_data)
	{
		free(old_data);
		return (0);
	}
	i = 0;
	while (i < prev_size && i < new_size)
	{
		((char*)new_data)[i] = ((char*)old_data)[i];
		++i;
	}
	free(old_data);
	return (new_data);
}

static inline void	ft_free_array(void **arr, size_t size,
		void (*free_data)(void*))
{
	size_t i;

	if (!free_data)
		return ;
	i = (size_t)-1;
	while (++i < size)
	{
		free_data(arr[i]);
	}
}

void		*ft_realloc_free(void *old_data, size_t prev_size, size_t new_size,
		void (*free_data)(void*))
{
	void	*new_data;
	size_t	i;

	if (!old_data)
		return (0);
	new_data = ft_memalloc(new_size);
	if (!new_data)
	{
		free(old_data);
		ft_free_array(old_data, prev_size, free_data);
		return (0);
	}
	i = 0;
	while (i < prev_size && i < new_size)
	{
		((char*)new_data)[i] = ((char*)old_data)[i];
		++i;
	}
	free(old_data);
	return (new_data);
}
