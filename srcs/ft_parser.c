/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggerardy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 18:37:52 by ggerardy          #+#    #+#             */
/*   Updated: 2019/04/09 18:21:08 by ggerardy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "len_in.h"

char g_invalid_flag_txt[] =
"Invalid option {Bold}{Red}%s{eof}.\n"
"Use {Bold}{Green}--help{eof} flags usage.\n";

char g_flags_usage_txt[] =
"{Bold}{Green}--usage{eof}     program usage.\n"
"{Bold}{Green}--help{eof}      flags usage.\n"
"{Bold}{Green}--fast{eof}      fast mode\n"
"            {Magenta}(enables minimal\n"
"             output format){eof}\n"
"{Bold}{Green}--vis{eof}       to enable visualizer.\n"
"{Bold}{Green}--file={eof}{Blue}file{eof} to specify input file\n"
"{Bold}{Green}--ants={eof}{Blue}file{eof} to specify file for ants' names.\n"
"{Bold}{Green}--format{eof}    to specify output format.\n"
"            {Blue}full{eof} - default format with map data "
"and ants movements\n"
"            {Blue}ants{eof} - only ants movements\n"
"            {Blue}minimal{eof} - only number of turns\n";

char g_prorgam_usage_txt[] =
"The program takes input data in format\n"
"     {Blue}number_of_ants{eof} (strictly {Magenta}positive{eof})\n"
"     {Blue}the_rooms{eof}      ({Magenta}any{eof} symbols you want)\n"
"                      mark start and end\n"
"                       with {Magenta}\"##start\"{eof}\n"
"                       or   {Magenta}\"##end\"{eof}\n"
"     {Blue}the_links{eof}      (as {Magenta}\"room1-room2\"{eof})\n";

int 	ft_set_flag(char *ln, t_pars *prs)
{
	if (!ft_strcmp(ln, "help"))
		return (ft_printf(g_flags_usage_txt) * 0);
	else if (!ft_strcmp(ln, "usage"))
		return (ft_printf(g_prorgam_usage_txt) * 0);
	else if (!ft_strcmp(ln, "fast"))
		return (SET_FAST(prs->flags) * 0 + 1);
	return (0);
}

t_pars	*ft_parse_flags(int ac, char **av)
{
	t_pars	*prs;
	int		i;

	if (!(prs = ft_memalloc(sizeof(t_pars))))
		return (0);
	i = 0;
	while (++i < ac)
	{
		if (av[i][0] != '-' || av[i][1] != '-' || !ft_set_flag(av[i] + 2, prs))
			return ((void*)(size_t)free_ret(prs, 0) +
				0 * ft_printf(g_invalid_flag_txt, av[i]));
	}
	ft_printf("%#hhB\n", prs->flags);

	return (prs);
}

t_data	*ft_parser(int fd)
{
	t_data		*dt;
	int 		parse_res;

	if (!(dt = ft_make_data()))
		return (0);
	if ((dt->ant_count = ft_parse_ants_count(fd, dt)) <= 0)
		return ((void*)(size_t)ft_free_data(dt, 0));
	if (!(parse_res = ft_parse_rooms(dt, fd)))
		return ((void*)(size_t)ft_free_data(dt, 0));
	if (!ft_check_start_end(dt))
		return ((void*)(size_t)ft_free_data(dt, 0));
	if (parse_res == -1)
		return (dt);
	if (!ft_parse_links(dt, fd))
		return ((void*)(size_t)ft_free_data(dt, 0));
	if (!(dt->heap = make_heap(dt->nodes->len)) ||
		!(dt->dsts = ft_memalloc(sizeof(int) * dt->nodes->len)) ||
		!(dt->ants = ft_memalloc(sizeof(t_ant) * dt->ant_count)) ||
		!(dt->gone_ants = ft_memalloc(dt->ant_count)) ||
		!ft_string_push_back(&dt->output, '\n'))
		return ((void*)(size_t)ft_free_data(dt, 0));
	return (dt);
}
