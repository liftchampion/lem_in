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
"            {Magenta}enables  --format=minimal\n"
"            disables --vis\n"
"            disables --ants=file{eof}\n"
"{Bold}{Green}--answer{eof}    {Bold}add{eof} to {Bold}stdout{eof} line with\n"
"            required movements count by generator.\n"
"{Bold}{Green}--vis{eof}       enable visualizer.\n"
"{Bold}{Green}--file={eof}{Blue}file{eof} specify input file.\n"
"{Bold}{Green}--ants={eof}{Blue}file{eof} specify file for ants' names.\n"
"{Bold}{Green}--format{eof}    specify output format:\n"
"            {Blue}full{eof} - default format with map data\n"
"                   and ants movements.\n"
"            {Blue}ants{eof} - only ants movements.\n"
"            {Blue}minimal{eof} - only number of turns.\n"
"{Bold}{Green}--flows{eof}     find {Bold}all{eof} flows and print it's info\n"
"            {Magenta}not working in special cases\n";

char g_program_usage_txt[] =
"The program takes input data in format:\n"
"    {Blue}number_of_ants{eof}  -strictly {Magenta}positive{eof}\n"
"    {Blue}the_rooms{eof}       -followed by {Magenta}\\n{eof}\n"
"                     mark start and end\n"
"                     with {Magenta}\"##start\"{eof}\n"
"                     and   {Magenta}\"##end\"{eof}\n"
"    {Blue}the_links{eof}       -as {Magenta}\"room1-room2\"{eof}\n";
