/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erlajoua <erlajoua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 18:06:25 by erlajoua          #+#    #+#             */
/*   Updated: 2021/03/01 20:12:52 by erlajoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		sort_builtin(t_cmd *cmd, t_list **envs)
{
	if (!ft_strcmp(cmd->cmds[0], "pwd"))
		ft_pwd(cmd);
	if (!ft_strcmp(cmd->cmds[0], "cd"))
		ft_cd(cmd, envs);
	if (!ft_strcmp(cmd->cmds[0], "env"))
		ft_env(cmd, envs);
	if (!(ft_strcmp(cmd->cmds[0], "unset")))
		ft_unset(cmd, envs);
	if (!(ft_strcmp(cmd->cmds[0], "echo")))
		ft_echo(cmd);
	if (!(ft_strcmp(cmd->cmds[0], "exit")))
		ft_exit(cmd);
	if (!(ft_strcmp(cmd->cmds[0], "export")))
		ft_export(cmd, *envs);
	return (1);
}
