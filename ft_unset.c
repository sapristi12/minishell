/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erlajoua <erlajoua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 15:08:26 by erlajoua          #+#    #+#             */
/*   Updated: 2021/03/12 11:22:07 by erlajoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int				condition_u(char *content, char *str, int index)
{
	if (index == 1)
	{
		if (!ft_strncmp(content, str, ft_strlen(str))
		&& content[ft_strlen(str)] == '=')
		{
			return (1);
		}
	}
	else if (index == 0)
	{	
		if (!ft_strncmp(content, str, ft_strlen(str)))
			return (1);
	}
	return (0);
}

void			ft_delone(t_list **lst, char *str, int index)
{
	t_list	*envs;
	t_list	*tmp;

	envs = *lst;
	if (condition_u(envs->content, str, index))
	{
		tmp = envs->next;
		free(envs->content);
		free(envs);
		*lst = tmp;
		return ;
	}
	while (envs)
	{
		if (condition_u(envs->content, str, index))
		{
			tmp->next = envs->next;
			free(envs->content);
			free(envs);
			envs = tmp;
		}
		tmp = envs;
		envs = envs->next;
	}
}

int				ft_unset(t_cmd *cmd, t_list **envs)
{
	int i;

	i = 1;
	while (cmd->cmds[i] && !is_symbol(cmd->cmds[i]))
	{
		if (cmd->cmds[i][0] == '/')
			error_identifier(cmd->cmds[i]);
		else
		{
			ft_delone(envs, cmd->cmds[i], 1);
			if (cmd->exported != NULL)
				ft_delone(&(cmd->exported), cmd->cmds[i], 0);
		}
		i++;
	}
	return (1);
}
