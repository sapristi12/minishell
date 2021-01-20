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
        minishell.h parsing.c create_space_around.c ft_strcmp.c free_parsing_line.c display.c parsing_pipe.c init_struct.c init_pipe.c args_package.c ft_strdup.c several_string.c parsing_quote.c parsing_redir.c count_string.c)
