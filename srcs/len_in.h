/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shapka                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggerardy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 22:34:17 by ggerardy          #+#    #+#             */
/*   Updated: 2019/04/09 22:34:17 by ggerardy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEN_IN_H
# define LEN_IN_H
# include "lem_in_structs.h"
# include "len_in.h"

/*
**	ft_parser.c
*/
int		ft_parse_ants_count(void);
int		ft_split_room(t_data *dt);
int		ft_parse_hash(t_data *dt, char *ln, t_parse_mode pm);
int		ft_parse_room(char *ln, t_data *dt);
int		ft_parse_rooms(t_data *dt);
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
