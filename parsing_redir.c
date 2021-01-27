#include "minishell.h"

static int     change_dup(t_cmd *cmd, int fdleft, int fdright)
{
    cmd->redir.save_left = get_left(cmd);
    cmd->redir.save_right = get_right(cmd);
    fdright = dup(STDOUT_FILENO);
    if (cmd->redir.save_left)
    {
        fdleft = open(cmd->redir.save_left, O_RDONLY);
        if (fdleft < 0)
            perror(cmd->redir.save_left);
        dup2(fdleft, STDIN_FILENO);
        close(fdleft);
    }
    if (cmd->redir.save_right && cmd->redir.mode == 'A')
		fdright = open(cmd->redir.save_right, O_WRONLY | O_CREAT | O_APPEND, 0777);
    else if (cmd->redir.save_right && cmd->redir.mode == 'T')
		fdright = open(cmd->redir.save_right, O_WRONLY | O_CREAT | O_TRUNC, 0777);
    if (fdright < 0)
    {
        perror(cmd->redir.save_right);
        return (0);
    }
    dup2(fdright, STDOUT_FILENO);
    close(fdright);
    return (1);
}

int     parsing_redir(t_cmd *cmd)
{
    cmd->redir.left = count_string(cmd->cmds, "<");
    cmd->redir.right = count_string(cmd->cmds, ">") + count_string(cmd->cmds, ">>");
	if (!(parse_redir_fd(cmd)))
        return (-1);
    if (!(change_dup(cmd, 0, 0)))
        return (-1);
    return (1);
}
