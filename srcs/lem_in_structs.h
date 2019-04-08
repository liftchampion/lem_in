/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggerardy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/31 09:33:52 by ggerardy          #+#    #+#             */
/*   Updated: 2019/03/31 09:33:52 by ggerardy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_STRUCTS_H
# define LEM_IN_STRUCTS_H

# include "libft.h"

# define NODE struct s_node
# define EDGE struct s_edge
# define HEAP struct s_heap

typedef NODE	t_node;
typedef EDGE	t_edge;
typedef HEAP	t_heap;

struct	s_node
{
	char		*name;
	t_vector	*children;
	t_vector	*parents;
	int			p;
	int 		x;
	int 		y;
};

struct	s_edge
{
	int	node;
	int	weight;
};

struct	s_heap
{
	int	*v;
	int len;
};

#endif
