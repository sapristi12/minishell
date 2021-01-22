cmake_minimum_required(VERSION 3.17)
project(new_shell C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(new_shell
    args_package.c
    check_first_command.c
    count_string.c
    create_space_around.c
    display.c
    free_parsing_line.c
    ft_errno.c
    ft_list.c
    ft_strcmp.c
    ft_strdup.c
    get_next_line.h
    get_next_line_utils.c
    init_list_env.c
    init_pipe.c
    init_struct.c
    main.c
    minishell.h
    new_split.c
    parsing.c
    parsing_pipe.c
    parsing_quote.c
    parsing_redir.c
    several_string.c get_next_line.c is_builtin.c get_path_command.c ft_stradd.c get_env.c create_args.c)
