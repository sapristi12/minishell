#include "minishell.h"

int     parsing_pipe(t_cmd *cmd)
{
    cmd->pipe.nb_pipe = count_string(cmd->cmds, "|");
    cmd->pipe.save = cmd->pipe.nb_pipe;
    return (1);
}
