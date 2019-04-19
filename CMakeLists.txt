cmake_minimum_required(VERSION 3.12.3)
project(lem_in C)

set(CMAKE_C_STANDARD 99)

add_compile_options(-Wall -Wextra)
include_directories(./libft/includes)
FILE(GLOB LIBFT_SRCS ./libft/*.c ./libft/*/*.c)

add_executable(lem_in ${LIBFT_SRCS} srcs/main.c srcs/lem_in_structs.h srcs/len_in.h
		srcs/ft_parser.c srcs/len_in.h srcs/ft_utils.c
		srcs/dijkstra.c srcs/ft_makers.c srcs/ft_freeshers.c
		srcs/ft_heap.c srcs/ft_parser_utils.c
		srcs/ft_parser_links.c srcs/ft_parser_rooms.c srcs/ft_shortest.c
		srcs/ft_flow_send.c srcs/ft_flow.c srcs/ft_lems.c srcs/ft_print_answer.c srcs/ft_usages.c srcs/ft_partitial_cases.c srcs/ft_parser_flags.c)
