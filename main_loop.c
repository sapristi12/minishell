/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erlajoua <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 13:24:58 by erlajoua          #+#    #+#             */
/*   Updated: 2021/03/11 20:16:30 by erlajoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include "minishell.h"

int		check_status(char **cmds, int status)
{
	if (status == -1)
		free_parsing_line(cmds, status);
	if (status == -2)
	{
		free_char_double_array(cmds);
		return (-1);
	}
	return (1);
}

int		free_split_null(char *prompt, char **cmds)
{
	free(prompt);
	free_char_double_array(cmds);
	ft_putstr_fd(
	"minishell: syntax error near unexpected ';'\n"
	, STDERR_FILENO);
	return (0);
}

void	ending_main_loop(char *str, char **cmds)
{
	if (str && !only_spaces(str))
		ft_putstr_fd(
		"minishell: syntax error near unexpected ';'\n", STDERR_FILENO);
	free_char_double_array(cmds);
}

int		free_status(char *prompt, int ret)
{
	if (ret == -2)
		free(prompt);
	return (-1);
}

int		main_loop(char *prompt, t_cmd *cmd, t_list **envs)
{
	int		i;
	int		status;
	char	**cmds;
	int		ret;

	i = 0;
	if (!check_prompt(1, prompt) || !check_prompt(2, prompt))
		return (0);
	if (!(cmds = new_split(prompt, ';')) || cmds[i] == NULL)
		return (free_split_null(prompt, cmds));
	while (cmds[i] && !only_spaces(cmds[i]))
	{
		if (!only_spaces(cmds[i]))
		{
			status = parsing_line(cmds[i], envs, cmd);
			if ((ret = check_status(cmds, status)) <= -1)
				return (free_status(prompt, ret));
		}
		i++;
	}
	ending_main_loop(cmds[i], cmds);
	return (0);
}
