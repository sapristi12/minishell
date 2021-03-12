/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erlajoua <erlajoua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 19:00:43 by erlajoua          #+#    #+#             */
/*   Updated: 2021/03/12 11:34:54 by erlajoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int				move_pointer_i(char **cmds)
{
	int i;

	i = 0;
	while (cmds[i] && ft_strcmp(cmds[i], "|"))
		i++;
	return (i + 1);
}

static int		execution_builtin(t_cmd *cmd, t_list **envs, int index)
{
	if (!(sort_builtin(cmd, envs, index)))
		return (0);
	return (1);
}

int				exec_child_pid(t_cmd *cmd, t_list **envs, int i)
{
	char	**envp;

	if (cmd->pipe.all[0][0] != NULL)
	{
		envp = list_to_array(*envs);
		ft_lstclear(envs, free);
		ft_lstclear(&(cmd->exported), free);
		if (execve(cmd->pipe.all[i][0], cmd->pipe.all[i], envp) == -1)
		{
			(errno == 2 || errno == 13) ? is_not_found(cmd->pipe.all[i][0],
			envp) : perror("minishell");
		}
		free_char_double_array(envp);
	}
	return (-1);
}

static int		execution_bin(t_cmd *cmd, t_list **envs, int i)
{
	int		status;

	status = 1;
	get_flag(SET, 1);
	cmd->pid = fork();
	if (cmd->pid == -1)
		perror("Fork");
	if (cmd->pid == 0)
		return (exec_child_pid(cmd, envs, i));
	waitpid(cmd->pid, &status, 0);
	if (WIFEXITED(status))
		g_sig = WEXITSTATUS(status);
	get_flag(SET, 0);
	if (g_sig == 126 && !ft_strcmp(cmd->pipe.all[i][0], ".."))
		g_sig = 127;
	if (cmd->pipe.all[i][0] && is_dir(cmd->pipe.all[i][0], 0)
	&& ft_strcmp(cmd->pipe.all[i][0], ".."))
		g_sig = 126;
	return (1);
}

int				exec_cmd(t_cmd *cmd, t_list **envs, int i)
{
	if (is_builtin(cmd->pipe.all[0][0]))
		return (execution_builtin(cmd, envs, i));
	else
		return (execution_bin(cmd, envs, i));
}
