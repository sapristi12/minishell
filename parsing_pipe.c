#include "minishell.h"

int     parsing_pipe(t_cmd *cmd)
{
    cmd->pipe.nb_pipe = count_string(cmd->cmds, "|");
    return (1);
}
