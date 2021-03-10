/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_redir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erlajoua <erlajoua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 17:54:00 by erlajoua          #+#    #+#             */
/*   Updated: 2021/03/09 10:14:46 by erlajoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		change_dup(t_cmd *cmd, int index, int fdleft, int fdright)
{
	cmd->redir.save_left = get_left(cmd, index);
	cmd->redir.save_right = get_right(cmd, index);
	fdright = dup(STDOUT_FILENO);
	if (cmd->redir.save_left)
	{
		fdleft = open(cmd->redir.save_left, O_RDONLY);
		if (fdleft < 0)
			perror(cmd->redir.save_left);
		dup2(fdleft, STDIN_FILENO);
		close(fdleft);
	}
	if (cmd->redir.save_right && cmd->redir.mode == 'A')
		fdright = open(cmd->redir.save_right,
		O_WRONLY | O_CREAT | O_APPEND, 0777);
	else if (cmd->redir.save_right && cmd->redir.mode == 'T')
		fdright = open(cmd->redir.save_right,
		O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fdright < 0)
	{
		perror(cmd->redir.save_right);
		return (0);
	}
	dup2(fdright, STDOUT_FILENO);
	close(fdright);
	return (1);
}

char			**pointer_package(char **cmds, int index)
{
	int i;
	int j;

	j = 0;
	i = 0;
	while (cmds[i] && j != index)
	{
		if (!ft_strcmp(cmds[i], "|"))
			j++;
		i++;
	}
	if (!ft_strcmp(cmds[i], "|"))
		return (&cmds[i + 1]);
	return (&cmds[i]);
}

int				parsing_redir(t_cmd *cmd, int index)
{
	char **strs;

	dup2(cmd->mystdout, STDOUT_FILENO);
	dup2(cmd->mystdin, STDIN_FILENO);
	strs = pointer_package(cmd->cmds, index);
	cmd->redir.right = 0;
	cmd->redir.left = 0;
	cmd->redir.save_right = NULL;
	cmd->redir.save_left = NULL;
	cmd->redir.left = count_string2(strs, "<", cmd->tab[index]);
	cmd->redir.right = count_string2(strs, ">", cmd->tab[index])
	+ count_string2(strs, ">>", cmd->tab[index]);
	if (!(parse_redir_fd(cmd, index, cmd->tab[index])))
		return (0);
	if (!(change_dup(cmd, index, 0, 0)))
		return (0);
	return (1);
}
