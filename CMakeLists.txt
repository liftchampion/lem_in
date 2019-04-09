cmake_minimum_required(VERSION 3.12.3)
project(lem_in C)

set(CMAKE_C_STANDARD 99)

add_compile_options(-Wall -Wextra)
include_directories(./libft/includes)
FILE(GLOB LIBFT_SRCS ./libft/*.c ./libft/*/*.c)

add_executable(lem_in ${LIBFT_SRCS} srcs/main.c srcs/lem_in_structs.h srcs/len_in.h
		srcs/ft_parser.c srcs/len_in.h libft/ft_free_ret.c srcs/ft_utils.c libft/ft_strsub_char.c srcs/dijkstra.c)
