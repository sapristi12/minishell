/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_first_command.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erlajoua <erlajoua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 17:53:21 by erlajoua          #+#    #+#             */
/*   Updated: 2021/03/01 18:16:19 by erlajoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		basic_first_command(char **cmds, t_list **envs, int *tab)
{
	char		**args;

	if (is_builtin(cmds[0]))
		return (1);
	if (!(args = create_package(cmds, envs, 1, tab)))
	{
		ft_putstr_fd(cmds[0], STDOUT_FILENO);
		ft_putstr_fd(": command not found\n", STDOUT_FILENO);
		return (0);
	}
	free_char_double_array(args);
	return (1);
}

int				pipe_first_command(t_cmd *cmd, t_list **envs)
{
	int i;
	int j;

	j = 1;
	i = 1;
	if (!(basic_first_command(cmd->cmds, envs, cmd->tab[0])))
		g_sig = 127;
	else
		g_sig = 0;
	while (cmd->cmds[i + 1])
	{
		if (!ft_strcmp(cmd->cmds[i], "|"))
		{
			if (!(basic_first_command(&(cmd->cmds[i + 1]), envs, cmd->tab[j])))
				g_sig = 127;
			else
				g_sig = 0;
			j++;
		}
		i++;
	}
	return (1);
}

int				check_first_command(t_cmd *cmd, t_list **envs)
{
	if (cmd->pipe.nb_pipe == 0)
	{
		if (!(basic_first_command(cmd->cmds, envs, cmd->tab[0])))
			g_sig = 127;
		else
			g_sig = 0;
	}
	return (1);
}
