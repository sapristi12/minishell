cmake_minimum_required(VERSION 3.16)
project(minishell C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(minishell
        check_first_command.c
        close.c
        count_string.c
        create_args.c
        create_new_str.c
        create_space_around.c
        display.c
        double_quote.c
        env.c
        exec_cmd.c
        export_create_env.c
        forking.c
        free_error.c
        free_parsing_line.c
        free_parsing_quote.c
        free_return.c
        ft_atoi.c
        ft_cd.c
        ft_echo.c
        ft_env.c
        ft_errno.c
        ft_exit.c
        ft_export.c
        ft_list.c
        ft_stradd.c
        ft_strcat.c
        ft_strcmp.c
        ft_strdup.c
        ft_strjoin.c
        ft_unset.c
        get_env.c
        get_next_line.c
        get_next_line.h
        get_next_line_utils.c
        get_path_command.c
        get_size_spaces.c
        get_tilde_path.c
        get_var_dollar.c
        init_list_env.c
        init_pipe.c
        init_struct.c
        is_builtin.c
        is_even_quote.c
        is_there_char.c
        is_token.c
        list_to_array.c
        loop_command_pipe.c
        main.c
        minishell.h
        move_pointer.c
        new_split.c
        parse_redir_fd.c
        parsing.c
        parsing_pipe.c
        parsing_quotes.c
        parsing_redir.c
        pwd.c
        quotes.c
        redir_save.c
        remove_escape_token.c
        several_string.c
        signal_handle.c
        sort_builtin.c
        sort_list.c is_only_spaces.c check_prompt.c only_zeros.c ft_export2.c is_not_found.c)