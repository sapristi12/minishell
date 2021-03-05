/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_command_pipe.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erlajoua <erlajoua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 20:16:19 by erlajoua          #+#    #+#             */
/*   Updated: 2021/03/05 17:09:30 by erlajoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	hub_close(t_cmd *cmd, int i)
{
	if (i == 0)
		close(cmd->pipe.fd[0][1]);
	else if (i == cmd->pipe.nb_pipe)
		close(cmd->pipe.fd[cmd->pipe.nb_pipe - 1][0]);
	else
		close_after(cmd, i);
}

void	hub_wait(t_cmd *cmd)
{
	int status;

	status = 0;
	waitpid(cmd->pid, &status, 0);
	if (WIFEXITED(status))
		g_sig = WEXITSTATUS(status);
}

int		loop_command_pipe(t_cmd *cmd, t_list **envs)
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
		dup2(cmd->mystdout, STDOUT_FILENO);
		dup2(cmd->mystdin, STDIN_FILENO);
		hub_wait(cmd);
		i++;
	}
	return (1);
}
