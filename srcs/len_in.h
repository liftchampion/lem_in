/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shapka                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggerardy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 11:00:43 by ggerardy          #+#    #+#             */
/*   Updated: 2019/04/24 11:00:43 by ggerardy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEN_IN_H
# define LEN_IN_H
# include "math.h"
# include "lem_in_structs.h"
# include "libft.h"
# include "len_in.h"

/*
**	dijkstra.c
*/
void			dijkstra(t_data *graf);
/*
**	ft_flow.c
*/
int				ft_restore_path(t_data *dt, int from, t_vector **path);
int				ft_flow_push_backs(t_data *dt, t_vector **flow,
			void **starts, int idx);
int				ft_restore_flow(t_data *dt);
int				ft_find_all_flows(t_data *dt);
/*
**	ft_flow_send.c
*/
int				ft_reverse_link(int i1, int i2, t_data *dt);
int				ft_send_flow(t_data *dt);
/*
**	ft_freeshers.c
*/
int				ft_free_node(t_node *nd, int ret);
int				ft_free_for_mlx(void *ptr);
int				ft_free_data(t_data *dt, int ret);
int				ft_free_heap(t_heap *hp, int ret);
/*
**	ft_heap.c
*/
void			sift_down(t_heap *heap, int ind);
void			sift_up(t_heap *heap, int ind);
int				take_min(t_heap *heap);
void			fill_heap(t_data *graf, t_heap *heap);
/*
**	ft_lems.c
*/
void			ft_send_lems_last_way(t_data *dt, int flow, int last_way,
			int ant_count);
int				ft_send_lems_one_flow(t_data *dt, int flow);
/*
**	ft_makers.c
*/
t_node			*ft_make_node(void);
t_data			*ft_make_data(t_pars *prs);
t_heap			*make_heap(int len);
/*
**	ft_parser.c
*/
t_data			*ft_parser(int fd, t_pars *prs);
/*
**	ft_parser_flags.c
*/
int				ft_append_ants_names(t_data *dt);
int				ft_parse_ants_names(t_data *dt);
int				ft_set_flag(char *ln, t_pars *prs);
void			*ft_parse_flags_end(t_pars *prs);
t_pars			*ft_parse_flags(int ac, char **av);
/*
**	ft_parser_links.c
*/
int				ft_add_link(int i1, int i2, t_data *dt);
int				ft_parse_link(char *ln, t_data *dt);
int				ft_parse_links(t_data *dt, int fd);
/*
**	ft_parser_rooms.c
*/
int				ft_split_room(t_data *dt);
int				ft_parse_room(char *ln, t_data *dt);
int				ft_parse_rooms(t_data *dt, int fd);
/*
**	ft_parser_utils.c
*/
int				ft_parse_ants_count(int fd, t_data *dt);
int				ft_parse_hash(t_data *dt, char *ln, t_parse_mode pm);
int				ft_check_links_begin(char *end, t_node *nd, t_data *dt);
int				ft_find_in_map(char *ln, t_data *dt);
int				ft_check_start_end(t_data *dt);
/*
**	ft_partitial_cases.c
*/
int				ft_print_murashi_simple(t_data *dt);
int				ft_procede_partitial_case(t_data *dt);
/*
**	ft_print_answer.c
*/
int				ft_fill_ants(t_data *dt);
int				ft_push_ant_move(t_data *dt, int i, t_vector **paths);
int				ft_print_murashi(t_data *dt);
/*
**	ft_shortest.c
*/
int				ft_find_shortest_path(t_data *dt);
/*
**	ft_utils.c
*/
void			ft_upd_pts(t_data *dt);
int				ft_check_file(char *name);
void			ft_sort_paths_in_flow(t_data *dt, int flow);
void			ft_print_flows(t_data *dt);
/*
**	ft_vis.c
*/
unsigned int	ft_get_color(t_data *dt, int i);
int				ft_lemin_keyhook(int key, void *p);
int				ft_mlx_expose(void *p);
int				ft_visualize(t_data *dt);
int				ft_visualize(t_data *dt);
/*
**	ft_vis_ants.c
*/
void			ft_fill_ants_poses(t_data *dt, const int *waves,
			int wave_count);
int				ft_vis_init_ants(t_data *dt);
void			ft_draw_ants(t_data *dt);
/*
**	ft_vis_dimensions.c
*/
void			ft_set_dims(t_data *dt, t_vis_dims *ds);
int				ft_get_dims_start(t_data *dt);
void			ft_get_dims_end(t_data *dt);
int				ft_get_dims(t_data *dt);
/*
**	ft_vis_drawers.c
*/
void			ft_print_map_one_unit(t_data *dt, int i, int x_pad, int y_pad);
void			ft_print_map(void *p);
void			ft_print_texts_one_unit(t_data *dt, int i, int x_pad,
			int y_pad);
void			ft_print_texts(void *p);
/*
**	ft_vis_init_works.c
*/
void			ft_fill_sorted_nodes(t_data *dt);
void			ft_rm_lines_from_output(t_data *dt);
void			ft_fill_names_to_pos(t_data *dt);
int				ft_copy_nodes(t_data *dt);
/*
**	ft_vis_text_works.c
*/
int				ft_check_text_nodes(t_data *dt);
int				ft_check_text_ants(t_data *dt);
/*
**	ft_vis_turns.c
*/
int				ft_turn_counter(t_data *dt, int turn);
void			ft_print_turns(t_vector **paths, int i, t_data *dt);
void			ft_turn(t_data *dt, int turn);

#endif
