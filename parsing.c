#include "minishell.h"

void    show_packages(t_cmd *cmd)
{
    int i;

    i = 0;
    while (cmd->cmds[i])
    {
        printf("%s\n", cmd->cmds[i]);
        i++;
    }
}

int     parsing_line(char *command, char **envp)
{
    char **cmds;
    t_cmd   cmd;

    init_struct_cmd(&cmd);
    if (!(number_quote_is_even(command)))
        return (-1);
    if (!(command = create_space_around(command)))
        return (-1);
    printf("%s\n", command);
    if (!(cmd.cmds = new_split(command, ' ')))
        return (-1);
    if (!parsing_pipe(&cmd))
        return (-1);
    show_packages(&cmd);
    if (!(parsing_redir(&cmd)))
        return (-1);
    free(command);
    free_char_double_array(cmd.cmds);
    return (0);
}
