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
"Use {Bold}{Green}--help{eof} to see flags usage.\n";

char g_flags_usage_txt[] =
"{Bold}{Green}--usage{eof}     program usage.\n"
"{Bold}{Green}--help{eof}      flags usage.\n"
"{Bold}{Green}--fast{eof}      fast mode.\n"
"            {Magenta}(enables  --format=minimal)\n"
"            (disables --vis)\n"
"            (disables --ants=file){eof}\n"
"{Bold}{Green}--vis{eof}       enable visualizer.\n"
"{Bold}{Green}--file={eof}{Blue}file{eof} specify input file.\n"
"{Bold}{Green}--ants={eof}{Blue}file{eof} specify file for ants' names.\n"
"{Bold}{Green}--format{eof}    specify output format:\n"
"            {Blue}full{eof} - default format with map data "
"and ants movements.\n"
"            {Blue}ants{eof} - only ants movements.\n"
"            {Blue}minimal{eof} - only number of turns.\n";

char g_prorgam_usage_txt[] =
"The program takes input data in format:\n"
"    {Blue}number_of_ants{eof}   (strictly {Magenta}positive{eof})\n"
"    {Blue}the_rooms{eof}        ({Magenta}any{eof} symbols you want)\n"
"                         mark start and end\n"
"                          with {Magenta}\"##start\"{eof}\n"
"                          or   {Magenta}\"##end\"{eof}\n"
"    {Blue}the_links{eof}        (as {Magenta}\"room1-room2\"{eof})\n";

int 	ft_append_ants_names(t_data *dt)
{
	int 	i;
	char 	*tmp_ln;
	int 	names_count;

	names_count = dt->ant_names->len;
	i = 0;
	while ((int)dt->ant_names->len < dt->ant_count)
	{
		ft_sprintf(&tmp_ln, "%s%d", dt->ant_names->data[i % names_count],
				i / names_count);
		++i;
		if (!tmp_ln || !ft_vector_push_back(&dt->ant_names, tmp_ln))
			return (0);
	}
	return (1);
}

int 	ft_parse_ants_names(t_data *dt)
{
	char	*ln;
	int		fd;

	if ((fd = open(dt->prs->ant_names, O_RDONLY)) == -1 ||
		!(dt->ant_names = ft_make_vector_free(dt->ant_count, free)))
		return (0);
	while ((int)dt->ant_names->len < dt->ant_count &&
		(ln = (char*)1lu) && ft_get_next_line(fd, &ln, READ_BUFF))
	{
		if (!ln)
			return (close(fd) * 0 * ft_get_next_line(fd, 0, READ_BUFF));
		if (!ft_vector_push_back(&dt->ant_names, ln))
			return (close(fd) * 0  * ft_get_next_line(fd, 0, READ_BUFF));
	}
	ft_get_next_line(fd, 0, READ_BUFF);
	if (!ft_append_ants_names(dt))
		return (close(fd) * 0);
	return (close(fd) * 0 + 1);
}

int 	ft_check_file(char *name)
{
	int fd;

	if (!name)
		return (-1);
	fd = open(name, O_RDONLY);
	if (fd == -1)
		return (0);
	if (read(fd, 0, 0) == -1)
	{
		close(fd);
		return (0);
	}
	close(fd);
	return (1);
}

int		ft_set_flag(char *ln, t_pars *prs)
{
	if (!ft_strcmp(ln, "help"))
		return (ft_printf(g_flags_usage_txt) * 0 - 1);
	else if (!ft_strcmp(ln, "usage"))
		return (ft_printf(g_prorgam_usage_txt) * 0 - 1);
	else if (!ft_strcmp(ln, "fast"))
		return (SET_FAST(prs->flags));
	else if (!ft_strcmp(ln, "vis"))
		return (SET_VIS(prs->flags) * 0 + 1);
	else if (!ft_strcmp(ln, "format=full"))
		return (SET_FMT_F(prs->flags) * 0 + 1);
	else if (!ft_strcmp(ln, "format=ants"))
		return (SET_FMT_A(prs->flags) * 0 + 1);
	else if (!ft_strcmp(ln, "format=minimal"))
		return (SET_FMT_M(prs->flags) * 0 + 1);
	else if (!ft_strncmp(ln, "file=", 5))
		return ((size_t)(prs->input_file = ln + 5) * 0 + 1);
	else if (!ft_strncmp(ln, "ants=", 5))
		return ((size_t)(prs->ant_names = ln + 5) * 0 + 1);
	return (0);
}

t_pars	*ft_parse_flags(int ac, char **av)
{
	t_pars	*prs;
	int		i;
	int 	flag_res;

	if (!(prs = ft_memalloc(sizeof(t_pars))))
		return
		((void*)(size_t)(ft_printf("Malloc error during parsing flags\n") * 0));
	SET_FMT_F(prs->flags);
	i = 0;
	while (++i < ac)
	{
		if (av[i][0] != '-' || av[i][1] != '-' ||
			(flag_res = ft_set_flag(av[i] + 2, prs)) <= 0)
			return ((void*)(size_t)free_ret(prs, 0) +
					0 * ft_printf(!flag_res ? g_invalid_flag_txt : "", av[i]));
	}
	if (!ft_check_file(prs->input_file))
		return ((void*)(size_t)free_ret(prs, 0) +
		0 * ft_printf("Bad file \"{Bold}{Red}%s{eof}\"\n", prs->input_file));
	if (GET_FAST(prs->flags) && !(prs->ant_names = 0))
		SET_FAST(prs->flags);
	if (!ft_check_file(prs->ant_names))
		return ((void*)(size_t)free_ret(prs, 0) +
		0 * ft_printf("Bad file \"{Bold}{Red}%s{eof}\"\n", prs->ant_names));
	return (prs);
}

t_data	*ft_parser(int fd, t_pars *prs)
{
	t_data		*dt;
	int 		parse_res;

	if (!(dt = ft_make_data(prs)))
		return (0);
	dt->prs = prs;
	if ((dt->ant_count = ft_parse_ants_count(fd, dt)) <= 0)
		return ((void*)(size_t)ft_free_data(dt, 0));
	if (!(parse_res = ft_parse_rooms(dt, fd)))
		return ((void*)(size_t)ft_free_data(dt, 0));
	if (!ft_check_start_end(dt))
		return ((void*)(size_t)ft_free_data(dt, 0));
	if (parse_res == -1) // todo gnl
		return (dt + 0 * ft_get_next_line(fd, 0, READ_BUFF));
	if (!ft_parse_links(dt, fd))
		return ((void*)(size_t)ft_free_data(dt, 0));
	if (!(dt->heap = make_heap(dt->nodes->len)) ||
		!(dt->dsts = ft_memalloc(sizeof(int) * dt->nodes->len)) ||
		!(dt->ants = ft_memalloc(sizeof(t_ant) * dt->ant_count)) ||
		!(dt->gone_ants = ft_memalloc(dt->ant_count)) ||
		!ft_string_push_back(&dt->output, '\n') ||
		(GET_FMT_A(prs->flags) &&
		!(dt->output = ft_make_string(INIT_OUTPUT_SIZE))))
		return ((void*)(size_t)ft_free_data(dt, 0));
	return (dt + 0 * ft_get_next_line(fd, 0, READ_BUFF));
}
