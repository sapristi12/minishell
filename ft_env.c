/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erlajoua <erlajoua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 17:46:47 by erlajoua          #+#    #+#             */
/*   Updated: 2021/03/03 10:01:12 by erlajoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_env(t_cmd *cmd, t_list **envs)
{
	int i;
	int j;

	j = 0;
	i = 0;
	while (cmd->cmds[i] && !is_symbol(cmd->cmds[i]))
	{
		if (!(ft_strcmp(cmd->cmds[i], "env")))
			j++;
		i++;
	}
	if (i > 1 && i != j)
	{
		ft_putstr_fd("env: ", STDERR_FILENO);
		ft_putstr_fd(cmd->cmds[1], STDERR_FILENO);
		ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
		return (1);
	}
	ft_afflist(envs);
	return (1);
}
