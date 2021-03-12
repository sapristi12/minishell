/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forking.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erlajoua <erlajoua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 17:49:22 by erlajoua          #+#    #+#             */
/*   Updated: 2021/03/12 10:23:36 by erlajoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		mid_fork(t_cmd *cmd, t_list **envs, int i)
{
	char	**envp;

	dup2(cmd->pipe.fd[i - 1][0], STDIN_FILENO);
	dup2(cmd->pipe.fd[i][1], STDOUT_FILENO);
	close_all(i - 1, cmd->pipe.nb_pipe, cmd->pipe.fd);
	if (is_builtin(cmd->pipe.all[i][0]))
		return (sort_builtin(cmd, envs, i));
	if (cmd->pipe.all[i][0] != NULL)
	{
		envp = list_to_array(*envs);
		ft_lstclear(envs, free);
		ft_lstclear(&(cmd->exported), free);
		if (execve(cmd->pipe.all[i][0], cmd->pipe.all[i], envp) == -1)
			(errno == 2 || errno == 13) ?
			is_not_found(cmd->pipe.all[i][0], envp) : perror("minishell");
		free_char_double_array(envp);
	}
	return (1);
}

int		last_fork(t_cmd *cmd, t_list **envs, int i)
{
	char	**envp;

	if (cmd->redir.save_left == NULL)
	{
		dup2(cmd->pipe.fd[cmd->pipe.nb_pipe - 1][0], STDIN_FILENO);
		close_last(i - 1, cmd->pipe.nb_pipe, cmd->pipe.fd);
	}
	if (is_builtin(cmd->pipe.all[i][0]))
		return (sort_builtin(cmd, envs, i));
	if (cmd->pipe.all[i][0] != NULL)
	{
		envp = list_to_array(*envs);
		ft_lstclear(envs, free);
		ft_lstclear(&(cmd->exported), free);
		if (execve(cmd->pipe.all[i][0], cmd->pipe.all[i], envp) == -1)
			(errno == 2 || errno == 13) ?
			is_not_found(cmd->pipe.all[i][0], envp) : perror("minishell");
		free_char_double_array(envp);
	}
	return (1);
}

int		first_fork(t_cmd *cmd, t_list **envs, int i)
{
	char	**envp;

	if (cmd->redir.save_right == NULL)
	{
		dup2(cmd->pipe.fd[0][1], STDOUT_FILENO);
		close_first(i + 1, cmd->pipe.nb_pipe, cmd->pipe.fd);
	}
	if (is_builtin(cmd->pipe.all[i][0]))
		return (sort_builtin(cmd, envs, i));
	if (cmd->pipe.all[i][0] != NULL)
	{
		envp = list_to_array(*envs);
		ft_lstclear(envs, free);
		ft_lstclear(&(cmd->exported), free);
		if (execve(cmd->pipe.all[i][0], cmd->pipe.all[i], envp) == -1)
			(errno == 2 || errno == 13) ?
			is_not_found(cmd->pipe.all[i][0], envp) : perror("minishell");
		free_char_double_array(envp);
	}
	return (1);
}
