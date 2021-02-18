#include "minishell.h"

static int  create_pipe(t_cmd *cmd)
{
    int i;

    i = 0;
    while (i < cmd->pipe.nb_pipe + 1)
    {
        if (pipe(cmd->pipe.fd[i]) == -1)
            return (-1);
        i++;
    }
    return (1);
}

static int  alloc_pipe(t_cmd *cmd)
{
    cmd->pipe.fd = malloc(sizeof(int[2]) * (cmd->pipe.nb_pipe + 1));
    if (!cmd->pipe.fd)
        return (-1);
    return (1);
}

int     init_pipe(t_cmd *cmd)
{
    if (alloc_pipe(cmd) == -1)
        return (-1);
    if (create_pipe(cmd) == -1)
        return (-1);
    return (1);
}
