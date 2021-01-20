#include "minishell.h"

static int  count_pipe(char **cmds)
{
    int     i;
    int     count;

    count = 0;
    i = 0;
    while (cmds[i])
    {
        if (!ft_strcmp(cmds[i], "|"))
            count++;
        i++;
    }
    return (count);
}

int     parsing_pipe(t_cmd *cmd)
{
    cmd->pipe.nb_pipe = count_pipe(cmd->cmds);
    return (0);
}
