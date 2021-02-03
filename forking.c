#include "minishell.h"

void	mid_fork(t_cmd *cmd, t_list **envs, int i)
{
	dup2(cmd->pipe.fd[i - 1][0], STDIN_FILENO);
	dup2(cmd->pipe.fd[i][1], STDOUT_FILENO);
	close_all(i - 1, cmd->pipe.nb_pipe, cmd->pipe.fd);
	exec_cmd(cmd, envs, i);
}

void	last_fork(t_cmd *cmd, t_list **envs, int i)
{
	dup2(cmd->pipe.fd[cmd->pipe.nb_pipe - 1][0], STDIN_FILENO);
	close_last(i - 1, cmd->pipe.nb_pipe, cmd->pipe.fd);
	exec_cmd(cmd, envs, i);
}

void	first_fork(t_cmd *cmd, t_list **envs, int i)
{
	dup2(cmd->pipe.fd[0][1], STDOUT_FILENO);
	close_first(i + 1, cmd->pipe.nb_pipe, cmd->pipe.fd);
	exec_cmd(cmd, envs, i);
}
