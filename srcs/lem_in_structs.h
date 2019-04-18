/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggerardy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/31 09:33:52 by ggerardy          #+#    #+#             */
/*   Updated: 2019/04/09 18:10:12 by ggerardy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_STRUCTS_H
# define LEM_IN_STRUCTS_H

# include "libft.h"

# define READ_BUFF 1000000

# define INF 1000000000
# define NOT_VISITED -57
# define LEFT weight[ind * 2 + 1]
# define RIGHT weight[ind * 2 + 2]
# define INIT_NODES_COUNT 128
# define INIT_NAME_LEN 16
# define INIT_PATH_LEN 64
# define INIT_LINKS_FROM_NODE 4
# define INIT_FLOW_COUNT 32
# define NODE_POSTFIX "_______"
# define TO_EDGE(i, w) ((void*)((((size_t)(i)) << 32u) | (unsigned)(w)))
# define GET_I(iw) ((int)((size_t)(iw) >> 32u))
# define GET_W(iw) ((int)(iw))
# define CN 0
# define OLD 1
# define NEW 2
# define CURR_PATH dt->ants[i].path
# define CURR_POS dt->ants[i].pos
# define PATH_LEN (int)paths[CURR_PATH]->len

# define NODE struct s_node
# define HEAP struct s_heap
# define DATA struct s_data
# define ANT struct s_ant
# define PMOD enum e_parse_mode

typedef NODE	t_node;
typedef HEAP	t_heap;
typedef DATA	t_data;
typedef ANT		t_ant;
typedef PMOD	t_parse_mode;

enum	e_parse_mode
{
	NODES,
	LINKS,
};

struct	s_data
{
	t_heap		*heap;
	t_vector	*nodes;
	char 		*tmp_line;
	t_map		*name_to_idx;
	int 		*dsts;
	t_vector	*path;
	t_vector	*flows;
	t_ant		*ants;
	char 		*gone_ants;
	int 		*wave_sizes;
	int 		ant_count;
	int 		start;
	int 		end;
	int 		best_flow;

};

struct	s_ant
{
	int	path;
	int pos;
};

struct	s_node
{
	char		*name;
	t_vector	*chs;
	int			p;
	int 		x;
	int 		y;
	int 		from;
};

struct	s_heap
{
	int	*weight;
	int	*name;
	int *num;
	int len;
};

#endif
