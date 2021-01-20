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
}

static int  alloc_pipe(t_cmd *cmd)
{
    cmd->pipe.fd = malloc(sizeof(int[2]) * (cmd->pipe.nb_pipe + 1));
    if (!cmd->pipe.fd)
        return (-1);
    cmd->pipe.all = malloc(sizeof(char **) * (cmd->pipe.nb_pipe + 2));
    if (!cmd->pipe.all)
        return (-1);
}

int     init_pipe(t_cmd *cmd)
{
    int i;

    i = 0;
    cmd->pipe.fd_saved = dup(STDIN_FILENO);
    if (alloc_pipe(cmd) == -1)
        return (-1);
    if (create_pipe(cmd) == -1)
        return (-1);
    if (!create_args(cmd))
        return (-1);
    dup2(cmd->pipe.fd_saved, STDIN_FILENO);
    return (1);
}
