/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_command_pipe.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erlajoua <erlajoua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 20:16:19 by erlajoua          #+#    #+#             */
/*   Updated: 2021/03/11 22:21:04 by erlajoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		hub_fork(t_cmd *cmd, t_list **envs, int i, int pid)
{
	int ret;

	ret = 0;
	if (pid == 0 && i == 0)
		ret = first_fork(cmd, envs, i);
	else if (pid == 0 && i != cmd->pipe.nb_pipe)
		ret = mid_fork(cmd, envs, i);
	else if (pid == 0 && i == cmd->pipe.nb_pipe)
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
	(void)cmd;
}

void	main_wait(int save, t_cmd *cmd, int *tab)
{
	/*long long int i;
	long long int timer;

	timer = 500000000;*/
	int i;
	int status;

	(void)cmd;
	i = 0;
	status = 0;
	while (save > 0)
	{
		waitpid(tab[save], &status, 0);
		if (WIFEXITED(status))
			g_sig = WEXITSTATUS(status);
		save--;
	}
}

int		loop_command_pipe(t_cmd *cmd, t_list **envs)
{
	int		i;
	int		ret;
	int		tab[3];

	i = 0;
	get_flag(SET, 1);
	while (i < cmd->pipe.nb_pipe + 1)
	{
		ret = 0;
		if (!(parsing_redir(cmd, i)))
			return (-2);
		tab[i] = fork();
		if (tab[i] == -1)
			return (-1);
		ret += hub_fork(cmd, envs, i, tab[i]);
		hub_close(cmd, i);
		if (ret == 1)
		{
			exit(0);
			return (-1);
		}
		dup2(cmd->mystdout, STDOUT_FILENO);
		dup2(cmd->mystdin, STDIN_FILENO);
		i++;
	}
	main_wait(cmd->pipe.nb_pipe + 1, cmd, tab);
	get_flag(SET, 0);
	return (1);
}
