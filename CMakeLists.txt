cmake_minimum_required(VERSION 3.10)
project(new_shell C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(new_shell
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
        parsing_redir.c
    several_string.c get_next_line.c is_builtin.c get_path_command.c ft_stradd.c get_env.c create_args.c redir_save.c parse_redir_fd.c exec_cmd.c forking.c close.c parsing_quotes.c ft_strcat.c ft_strjoin.c quotes.c free_return.c sort_builtin.c pwd.c ft_cd.c env.c ft_env.c ft_unset.c list_to_array.c free_error.c double_quote.c get_tilde_path.c ft_echo.c ft_exit.c is_token.c signal_handle.c ft_atoi.c sort_list.c ft_export.c export_create_env.c is_there_char.c free_parsing_quote.c remove_escape_token.c loop_command_pipe.c)
