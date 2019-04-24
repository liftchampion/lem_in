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
# include <fcntl.h>
# include <zconf.h>



int 	ft_mlx_expose(void *p);
int 	ft_lemin_keyhook(int key, void *p);




# define READ_BUFF_FILE 500000
# define READ_BUFF_STDIN 1000
# define INF 1000000000
# define NOT_VISITED -57
# define LEFT weight[ind * 2 + 1]
# define RIGHT weight[ind * 2 + 2]
# define INIT_NODES_COUNT 128
# define INIT_NAME_LEN 16
# define INIT_PATH_LEN 64
# define INIT_LINKS_FROM_NODE 4
# define INIT_FLOW_COUNT 32
# define INIT_OUTPUT_SIZE 1024
# define NODE_POSTFIX "_______"
# define CN 0
# define OLD 1
# define NEW 2

# define TO_EDGE(i, w) ((void*)((((size_t)(i)) << 32u) | (unsigned)(w)))
# define GET_I(iw) ((int)((size_t)(iw) >> 32u))
# define GET_W(iw) ((int)(iw))
# define CURR_PATH dt->ants[i].path
# define CURR_POS dt->ants[i].pos
# define PATH_LEN (int)paths[CURR_PATH]->len

# define SET_FAST(flags)     ((flags) = 0B00001001u | ((flags) & 0B01100000u))
# define SET_FMT_F(flags)    ((flags) = (((flags) & 0B11110001u) | (1u << 1u)))
# define SET_FMT_A(flags)    ((flags) = (((flags) & 0B11110001u) | (1u << 2u)))
# define SET_FMT_M(flags)    ((flags) = (((flags) & 0B11110001u) | (1u << 3u)))
# define SET_VIS(flags)      ((flags) |= 1u << 4u)
# define SET_ANSWER(flags)   ((flags) |= 1u << 5u)
# define SET_FLOWS(flags)   ((flags) |= 1u << 6u)
# define UNSET_ANSWER(flags) ((flags) &= 0B11011111u)
# define GET_FAST(flags)    (((flags) & (1u << 0u)) != 0)
# define GET_FMT_F(flags)   (((flags) & (1u << 1u)) != 0)
# define GET_FMT_A(flags)   (((flags) & (1u << 2u)) != 0)
# define GET_FMT_M(flags)   (((flags) & (1u << 3u)) != 0)
# define GET_VIS(flags)     (((flags) & (1u << 4u)) != 0)
# define GET_ANSWER(flags)  (((flags) & (1u << 5u)) != 0)
# define GET_FLOWS(flags)  (((flags) & (1u << 6u)) != 0)

#define DEFAULT_V_PAD 20
#define DEFAULT_H_PAD 20

extern char g_invalid_flag_txt[];
extern char g_flags_usage_txt[];
extern char g_program_usage_txt[];

# define NODE		struct s_node
# define HEAP		struct s_heap
# define DATA		struct s_data
# define ANT		struct s_ant
# define PRS		struct s_pars
# define VIS_NODE	struct s_vis_node
# define VIS_DIMS	struct s_vis_dims
# define PMOD		enum e_parse_mode

typedef NODE		t_node;
typedef HEAP		t_heap;
typedef DATA		t_data;
typedef ANT			t_ant;
typedef PRS			t_pars;
typedef PMOD		t_parse_mode;
typedef VIS_NODE	t_vis_node;
typedef VIS_DIMS	t_vis_dims;

enum	e_parse_mode
{
	NODES,
	LINKS,
};

struct	s_data
{
	t_heap		*heap;
	t_vector	*nodes;
	t_map		*name_to_idx;
	int 		*dsts;
	t_vector	*path;
	t_vector	*flows;
	t_ant		*ants;
	char 		*gone_ants;
	int 		*wave_sizes;
	t_string	*output;
	t_pars		*prs;
	t_vector	*ant_names;
	t_mlx		*mlx;
	t_vis_node	*sorted_nodes; //todo free
	int 		*name_to_pos; // todo free
	t_vis_dims	*dims; //todo free
	int 		screen_h;
	int 		screen_w;
	int 		real_nodes_count;
	int 		max_dst;
	int 		buff_size;
	int 		ant_count;
	int 		start;
	int 		end;
	int 		best_flow;
	int 		turns;
	int 		special_case;
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

struct	s_pars
{
	char			*input_file;
	char			*ant_names;
	unsigned char	flags;
};

struct	s_vis_node
{
	int name;
	int dst;
};

struct	s_vis_dims
{
	int	side;
	int	lines_count;
	int gap;
	int v_pad;
	int h_pad;
	int line_len;
	int h;
	int width;
	int height;
	int use_text_nodes;
	int use_text_ants;
	int longest_ant_name;
};

struct	s_heap
{
	int	*weight;
	int	*name;
	int *num;
	int len;
};

#endif
