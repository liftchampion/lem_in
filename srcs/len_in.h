/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shapka                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggerardy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 19:59:45 by ggerardy          #+#    #+#             */
/*   Updated: 2019/04/08 20:00:15 by ggerardy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEN_IN_H
# define LEN_IN_H
# include "lem_in_structs.h"
# include "len_in.h"

/*
**	ft_parser.c
*/
int			ft_parse_ants_count(void);
int			ft_parse_rooms(t_data *dt);
t_vector	*ft_parser(void);
/*
**	ft_utils.c
*/
int 		ft_free_data(t_data *dt, int ret);


void		ft_print_parsed(t_data *dt);

#endif
