#include "minishell.h"

int     parsing_line(char *command, char **envp)
{
    char **cmds;
    t_cmd   cmd;

    init_struct_cmd(&cmd);
    if (!(command = create_space_around(command)))
        return (-1);
    if (!(cmd.cmds = new_split(command, ' ')))
        return (-1);
    parsing_pipe(&cmd);
    //parsing_redir(&cmd);
    free(command);
    free_char_double_array(cmd.cmds);
    return (0);
}
