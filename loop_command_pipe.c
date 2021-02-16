#include "minishell.h"

int 	transform_token(t_cmd *cmd)
{
	int		i;
	int 	j;
	char 	*tmp;

	i = 0;
	while (cmd->pipe.all[i])
	{
		j = 0;
		while (cmd->pipe.all[i][j])
		{
			tmp = remove_escaped_token(cmd->pipe.all[i][j]);
			free(cmd->pipe.all[i][j]);
			cmd->pipe.all[i][j] = tmp;
			j++;
		}
		i++;
	}
}

int		hub_fork(t_cmd *cmd, t_list **envs, int i)
{
	int ret;

	ret = 0;
	if (cmd->pid == 0 && i == 0)
		ret = first_fork(cmd, envs, i);
	else if (cmd->pid == 0 && i != cmd->pipe.nb_pipe)
		ret = mid_fork(cmd, envs, i);
	else if (cmd->pid == 0 && i == cmd->pipe.nb_pipe)
		ret = last_fork(cmd, envs, i);
	return (ret);
}

void 	hub_close(t_cmd *cmd, int i)
{
	if (i == 0)
		close(cmd->pipe.fd[0][1]);
	else if (i == cmd->pipe.nb_pipe)
		close(cmd->pipe.fd[cmd->pipe.nb_pipe - 1][0]);
	else
		close_after(cmd, i);
}

int 	loop_command_pipe(t_cmd *cmd, t_list **envs)
{
	int i;
	int ret;

	i = 0;
	while (i < cmd->pipe.nb_pipe + 1)
	{
		ret = 0;
		if (!(parsing_redir(cmd, i)))
			return (-2);
		cmd->pid = fork();
		if (cmd->pid == -1)
			return (-1);
		ret += hub_fork(cmd, envs, i);
		hub_close(cmd, i);
		if (ret == 1)
			return (-1);
		i++;
	}
	while (cmd->pipe.save-- >= 0)
		wait(&(cmd->pid));
	return (1);
}
