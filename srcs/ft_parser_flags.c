/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser_flags.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggerardy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 08:39:00 by ggerardy          #+#    #+#             */
/*   Updated: 2019/04/19 08:39:00 by ggerardy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "len_in.h"

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
			(ln = (char*)1lu) && ft_get_next_line(fd, &ln, READ_BUFF_FILE))
	{
		if (!ln)
			return (close(fd) * 0 * ft_get_next_line(fd, 0, READ_BUFF_FILE));
		if (!ft_vector_push_back(&dt->ant_names, ln))
			return (close(fd) * 0  * ft_get_next_line(fd, 0, READ_BUFF_FILE));
	}
	ft_get_next_line(fd, 0, READ_BUFF_FILE);
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
		return (ft_printf(g_program_usage_txt) * 0 - 1);
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
	else if (!ft_strcmp(ln, "answer"))
		return (SET_ANSWER(prs->flags) * 0 + 1);
	else if (!ft_strcmp(ln, "flows"))
		return (SET_FLOWS(prs->flags) * 0 + 1);
	return (0);
}

t_pars	*ft_parse_flags(int ac, char **av)
{
	t_pars	*prs;
	int		i;
	int 	flag_res;

	if (!(prs = ft_memalloc(sizeof(t_pars))) || (flag_res = 0))
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
