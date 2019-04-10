/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shapka                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmiklaz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 05:04:56 by bmiklaz           #+#    #+#             */
/*   Updated: 2019/04/10 05:04:56 by bmiklaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEN_IN_H
# define LEN_IN_H
# include "lem_in_structs.h"
# include "len_in.h"

/*
**	dijkstra.c
*/
void	sift_down(t_heap *heap, int ind);
void	sift_up(t_heap *heap, int ind);
int		take_min(t_heap *heap);
t_heap	*make_heap(int len);
void	fill_heap(t_data *graf);
void	dijkstra(t_data *graf);
/*
**	ft_parser.c
*/
int		ft_parse_ants_count(void);
int		ft_split_room(t_data *dt);
int		ft_parse_hash(t_data *dt, char *ln, t_parse_mode pm);
int 	ft_find_in_map(char *ln, t_data *dt);
int 	ft_parse_link(char *ln, t_data *dt);
int 	ft_check_links_begin(char *end, t_node *nd, t_data *dt);
int		ft_parse_room(char *ln, t_data *dt);
int		ft_parse_rooms(t_data *dt);
int 	ft_check_start_end(t_data *dt);
t_data	*ft_parser(void);
/*
**	ft_utils.c
*/
t_node	*ft_make_node(void);
t_data	*ft_make_data(void);
int 	ft_free_node(t_node *nd, int ret);
int 	ft_free_data(t_data *dt, int ret);
void	ft_print_parsed(t_data *dt);

#endif
