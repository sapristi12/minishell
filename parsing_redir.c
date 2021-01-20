#include "minishell.h"

static int  is_several_redir(t_cmd *cmd)
{
    char    *strs[3];
    int     i;

    i = 0;
    strs[0] = ">";
    strs[1] = ">>";
    strs[2] = "<";
    while (i < 3)
    {
        if (!several_string(cmd->cmds, strs[i]))
            return (0);
        i++;
    }
    return (1);
}

int     parsing_redir(t_cmd *cmd)
{
    cmd->redir.left = count_string(cmd->cmds, "<");
    cmd->redir.right = count_string(cmd->cmds, ">") + count_string(cmd->cmds, ">>");
    if (!is_several_redir(cmd))
        return (-1);
}
