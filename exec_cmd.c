/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erlajoua <erlajoua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 19:00:43 by erlajoua          #+#    #+#             */
/*   Updated: 2021/03/05 10:11:45 by erlajoua         ###   ########.fr       */
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

int				init_all_package(t_cmd *cmd, t_list **envs)
{
	int len;
	int i;
	int pointer;

	i = 0;
	pointer = 0;
	len = cmd->pipe.nb_pipe;
	cmd->pipe.all = malloc(sizeof(char **) * (len + 2));
	if (!cmd->pipe.all)
		return (-1);
	cmd->pipe.all[len + 1] = NULL;
	while (i < len + 1)
	{
		cmd->pipe.all[i] = create_package(&(cmd->cmds[pointer]),
		envs, 0, cmd->tab[i]);
		pointer += move_pointer_i(&(cmd->cmds[pointer]));
		i++;
	}
	return (1);
}

static int		execution_builtin(t_cmd *cmd, t_list **envs)
{
	if (!(sort_builtin(cmd, envs)))
		return (0);
	return (1);
}

static int		execution_bin(t_cmd *cmd, t_list **envs, int i)
{
	char	**envp;
	int		status;

	cmd->pid = fork();
	status = 1;
	if (cmd->pid == -1)
		perror("Fork");
	if (cmd->pid == 0)
	{
		if (cmd->pipe.all[0][0] != NULL)
		{
			envp = list_to_array(*envs);
			ft_lstclear(envs, free);
			execve(cmd->pipe.all[i][0], cmd->pipe.all[i], envp);
			free_char_double_array(envp);
		}
		return (-1);
	}
	waitpid(cmd->pid, &status, 0);
	if (WIFEXITED(status))
		g_sig = WEXITSTATUS(status);
	return (1);
}

int				exec_cmd(t_cmd *cmd, t_list **envs, int i)
{
	if (is_builtin(cmd->pipe.all[0][0]))
		return (execution_builtin(cmd, envs));
	else
		return (execution_bin(cmd, envs, i));
}
