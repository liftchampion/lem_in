/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_usages.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggerardy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 08:33:00 by ggerardy          #+#    #+#             */
/*   Updated: 2019/04/19 08:33:00 by ggerardy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

char g_program_usage_txt[] =
"The program takes input data in format:\n"
"    {Blue}number_of_ants{eof}   (strictly {Magenta}positive{eof})\n"
"    {Blue}the_rooms{eof}        ({Magenta}any{eof} symbols you want)\n"
"                         mark start and end\n"
"                          with {Magenta}\"##start\"{eof}\n"
"                          or   {Magenta}\"##end\"{eof}\n"
"    {Blue}the_links{eof}        (as {Magenta}\"room1-room2\"{eof})\n";
