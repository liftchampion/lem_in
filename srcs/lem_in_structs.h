/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggerardy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/31 09:33:52 by ggerardy          #+#    #+#             */
/*   Updated: 2019/04/08 21:31:07 by ggerardy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_STRUCTS_H
# define LEM_IN_STRUCTS_H

# include "libft.h"

# define READ_BUFF 1000000

# define NODE struct s_node
# define EDGE struct s_edge
# define HEAP struct s_heap
# define DATA struct s_data

typedef NODE	t_node;
typedef EDGE	t_edge;
typedef HEAP	t_heap;
typedef DATA	t_data;

struct s_data
{
	t_vector	*nodes;
	char 		*tmp_line;
	t_map		*name_to_idx;
	int 		*dsts;
	int 		ant_count;
	int 		start;
	int 		end;
};

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
