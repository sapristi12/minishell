/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_token.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erlajoua <erlajoua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 20:20:15 by erlajoua          #+#    #+#             */
/*   Updated: 2021/03/01 20:20:27 by erlajoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		is_token_char(char c)
{
	if (c == '|')
		return (1);
	if (c == '>')
		return (1);
	if (c == '<')
		return (1);
	return (0);
}

int		is_token_string(char *str)
{
	if (!(ft_strcmp(str, "|")))
		return (1);
	if (!(ft_strcmp(str, ">>")))
		return (1);
	if (!(ft_strcmp(str, ">")))
		return (1);
	if (!(ft_strcmp(str, "<")))
		return (1);
	return (0);
}

int		check_last(char **cmds, int *tab)
{
	int i;

	i = 0;
	if (is_token_string(cmds[0]) && tab[0] == 1)
		return (0);
	while (cmds[i] && ft_strcmp(cmds[i], "|"))
		i++;
	if (i > 0 && (is_token_string(cmds[i - 1]) && tab[i - 1] == 1))
		return (0);
	return (1);
}

int		is_token_last(t_cmd *cmd)
{
	int i;
	int pointer;

	i = 0;
	pointer = 0;
	while (i < cmd->pipe.nb_pipe + 1)
	{
		if (!(check_last(&(cmd->cmds[pointer]), cmd->tab[i])))
			return (0);
		pointer += move_pointer_i(&(cmd->cmds[pointer]));
		i++;
	}
	return (1);
}
