/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_all_package.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erlajoua <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 13:05:38 by erlajoua          #+#    #+#             */
/*   Updated: 2021/03/11 13:19:48 by erlajoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		envs, cmd->tab[i]);
		pointer += move_pointer_i(&(cmd->cmds[pointer]));
		i++;
	}
	return (1);
}
