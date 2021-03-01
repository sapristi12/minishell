/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redir_fd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erlajoua <erlajoua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 17:59:43 by erlajoua          #+#    #+#             */
/*   Updated: 2021/03/01 17:59:59 by erlajoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		left_redir(char **cmds)
{
	int fd;

	fd = open(cmds[1], O_RDONLY);
	if (fd < 0)
	{
		perror(cmds[1]);
		return (0);
	}
	close(fd);
	return (1);
}

int		right_redir(char **cmds)
{
	int fd;

	fd = open(cmds[1], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fd < 0)
	{
		perror(cmds[1]);
		return (0);
	}
	close(fd);
	return (1);
}

int		rightright_redir(char **cmds)
{
	int fd;

	fd = open(cmds[1], O_WRONLY | O_CREAT | O_APPEND, 0777);
	if (fd < 0)
	{
		perror(cmds[1]);
		return (0);
	}
	close(fd);
	return (1);
}

int		parse_redir_fd(t_cmd *cmd, int index, int *tab)
{
	int		i;
	char	**strs;

	i = 0;
	strs = pointer_package(cmd->cmds, index);
	while (strs[i + 1] && ft_strcmp(strs[i + 1], "|"))
	{
		if (!ft_strcmp(strs[i], "<") && tab[i] == 1)
		{
			if (!(left_redir(&strs[i])))
				return (0);
		}
		else if (!ft_strcmp(strs[i], ">") && tab[i] == 1)
		{
			if (!(right_redir(&strs[i])))
				return (0);
		}
		else if (!ft_strcmp(strs[i], ">>") && tab[i] == 1)
		{
			if (!(rightright_redir(&strs[i])))
				return (0);
		}
		i++;
	}
	return (1);
}
