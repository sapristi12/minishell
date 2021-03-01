/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erlajoua <erlajoua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 15:10:29 by erlajoua          #+#    #+#             */
/*   Updated: 2021/03/01 15:14:16 by erlajoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			error_identifier(char *str)
{
	ft_putstr_fd("minishell: export: ", 1);
	ft_putstr_fd(str, 1);
	ft_putstr_fd(": not a valid identifier\n", 1);
	return (1);
}

void		add_new_export(t_list *envs, char *str)
{
	int		i;
	char	*tmp;

	tmp = malloc(1);
	if (!tmp)
		return ;
	tmp[0] = '\0';
	i = 0;
	while (str[i] && str[i] != '=')
	{
		tmp = char_strjoin(tmp, str[i]);
		i++;
	}
	if (!(get_env(envs, tmp)))
		ft_lstadd_back(&envs, ft_lstnew(str));
	else
		set_env(&envs, tmp, &str[i + 1]);
}

int			is_notidentifier(char *str)
{
	if (is_there_char(str, '=') == 0)
	{
		if (!is_alpha(str[0]))
			return (1);
	}
	return (0);
}

static int	manage_export(t_cmd *cmd, t_list *envs, int i)
{
	if (i == 1)
		return (export_list(envs));
	if (i == 2)
		return (error_identifier(cmd->cmds[1]));
	return (1);
}

int			ft_export(t_cmd *cmd, t_list *envs)
{
	char	*tmp;
	int		i;

	i = 0;
	while (cmd->cmds[i] && !is_symbol(cmd->cmds[i]))
		i++;
	if (i == 1 || (i == 2 && is_notidentifier(cmd->cmds[1])))
		return (manage_export(cmd, envs, i));
	i = 1;
	while (cmd->cmds[i] && !is_symbol(cmd->cmds[i]))
	{
		if (is_there_char(cmd->cmds[i], '='))
		{
			if (!(tmp = create_env(cmd->cmds[i])))
				error_identifier(cmd->cmds[i]);
			else
			{
				add_new_export(envs, tmp);
				free(tmp);
			}
		}
		i++;
	}
	return (1);
}
