/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_parsing_line.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erlajoua <erlajoua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 17:50:09 by erlajoua          #+#    #+#             */
/*   Updated: 2021/03/10 16:30:48 by erlajoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		free_package(t_cmd *cmd)
{
	int i;

	i = 0;
	while (cmd->pipe.all[i])
	{
		free_char_double_array(cmd->pipe.all[i]);
		i++;
	}
	free(cmd->pipe.all);
}

int			free_8(char *str, t_cmd *cmd, int ret)
{
//	printf("SIG : %d\n", g_sig);
//	if (g_sig != 127)
//		g_sig = 2;
//	printf("SIG : %d\n", g_sig);
	free_int_double_array(cmd);
	free(str);
	free_char_double_array(cmd->cmds);
	return (ret);
}

void		free_char_double_array(char **strs)
{
	int i;

	i = 0;
	while (strs[i])
	{
		free(strs[i]);
		i++;
	}
	free(strs);
}

int			free_i(t_cmd *cmd, int index)
{
	free_char_double_array(cmd->cmds);
	return (index);
}

int			free_parsing_line(char **av, int status)
{
	int i;

	i = 0;
	if (status == -2)
		free_char_double_array(av);
	return (1);
}
