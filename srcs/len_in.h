/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shapka                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggerardy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/20 06:09:45 by ggerardy          #+#    #+#             */
/*   Updated: 2019/04/20 06:09:45 by ggerardy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEN_IN_H
# define LEN_IN_H
# include "lem_in_structs.h"
# include "libft.h"
# include "len_in.h"

/*
**	dijkstra.c
*/
void	dijkstra(t_data *graf);
/*
**	ft_flow.c
*/
int 	ft_restore_path(t_data *dt, int from, t_vector **path);
int 	ft_flow_push_backs(t_data *dt, t_vector **flow, void **starts, int idx);
int		ft_restore_flow(t_data *dt);
int		ft_find_all_flows(t_data *dt);
/*
**	ft_flow_send.c
*/
int		ft_reverse_link(int i1, int i2, t_data *dt);
int		ft_send_flow(t_data *dt);
/*
**	ft_freeshers.c
*/
int 	ft_free_node(t_node *nd, int ret);
int 	ft_free_for_mlx(void *ptr);
int 	ft_free_data(t_data *dt, int ret);
int 	ft_free_heap(t_heap *hp, int ret);
/*
**	ft_heap.c
*/
void	sift_down(t_heap *heap, int ind);
void	sift_up(t_heap *heap, int ind);
int		take_min(t_heap *heap);
void	fill_heap(t_data *graf, t_heap *heap);
/*
**	ft_lems.c
*/
void	ft_send_lems_last_way(t_data *dt, int flow, int last_way,
		int ant_count);
int 	ft_send_lems_one_flow(t_data *dt, int flow);
/*
**	ft_makers.c
*/
t_node	*ft_make_node(void);
t_data	*ft_make_data(t_pars *prs);
t_heap	*make_heap(int len);
/*
**	ft_parser.c
*/
t_data	*ft_parser(int fd, t_pars *prs);
/*
**	ft_parser_flags.c
*/
int 	ft_append_ants_names(t_data *dt);
int 	ft_parse_ants_names(t_data *dt);
int 	ft_check_file(char *name);
int		ft_set_flag(char *ln, t_pars *prs);
t_pars	*ft_parse_flags(int ac, char **av);
/*
**	ft_parser_links.c
*/
int 	ft_add_link(int i1, int i2, t_data *dt);
int 	ft_parse_link(char *ln, t_data *dt);
int 	ft_parse_links(t_data *dt, int fd);
/*
**	ft_parser_rooms.c
*/
int		ft_split_room(t_data *dt);
int		ft_parse_room(char *ln, t_data *dt);
int		ft_parse_rooms(t_data *dt, int fd);
/*
**	ft_parser_utils.c
*/
int		ft_parse_ants_count(int fd, t_data *dt);
int		ft_parse_hash(t_data *dt, char *ln, t_parse_mode pm);
int 	ft_check_links_begin(char *end, t_node *nd, t_data *dt);
int 	ft_find_in_map(char *ln, t_data *dt);
int 	ft_check_start_end(t_data *dt);
/*
**	ft_partitial_cases.c
*/
int 	ft_print_murashi_simple(t_data *dt);
int 	ft_procede_partitial_case(t_data *dt);
/*
**	ft_print_answer.c
*/
int 	ft_fill_ants(t_data *dt);
int 	ft_push_ant_move(t_data *dt, int i, t_vector **paths);
int		ft_print_murashi(t_data *dt);
/*
**	ft_shortest.c
*/
int		ft_find_shortest_path(t_data *dt);
/*
**	ft_utils.c
*/
void	ft_upd_pts(t_data *dt);
void	ft_sort_paths_in_flow(t_data *dt, int flow);
int 	ft_check_generator_flags(char *ln);
/*
**	ft_vis_save_nodes.c
*/
void 	ft_fill_sorted_nodes(t_data *dt);
void 	ft_fill_names_to_pos(t_data *dt);
int 	ft_copy_nodes(t_data *dt);

#endif
