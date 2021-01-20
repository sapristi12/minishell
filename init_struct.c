#include "minishell.h"

void    init_struct_pipe(t_pipe *pipe)
{
    pipe->nb_pipe = 0;
    pipe->save = 0;
    pipe->all = NULL;
    pipe->fd = NULL;
    pipe->fd_saved = 0;
    pipe->pid = 0;
}

void    init_struct_cmd(t_cmd *cmd)
{
    cmd->cmds = NULL;
    init_struct_pipe(&cmd->pipe);
}
