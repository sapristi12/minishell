cmake_minimum_required(VERSION 3.17)
project(parsing C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(parsing
        get_next_line.c
        get_next_line.h
        new_split.c
        get_next_line_utils.c
        main.c
        minishell.h parsing.c create_space_around.c ft_strcmp.c)
