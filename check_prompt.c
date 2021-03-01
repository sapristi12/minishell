/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_prompt.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erlajoua <erlajoua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 20:07:14 by erlajoua          #+#    #+#             */
/*   Updated: 2021/03/01 20:18:04 by erlajoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		multiple_semicolon(char *str)
{
	int i;

	i = 0;
	if (str[0] == ';')
		return (0);
	while (str[i + 1])
	{
		if (str[i] == ';' && str[i + 1] == ';')
			return (0);
		if (str[i] == ';')
		{
			i++;
			while (str[i] && str[i] == ' ')
				i++;
			if (str[i] == ';')
				return (0);
		}
		i++;
	}
	return (1);
}

int		check_prompt(int index, char *prompt)
{
	if (index == 1)
	{
		if (only_spaces(prompt))
		{
			free(prompt);
			return (0);
		}
	}
	else if (index == 2)
	{
		if (!multiple_semicolon(prompt))
		{
			ft_putstr_fd(
			"minishell: syntax error near unexpected ';'\n", STDERR_FILENO);
			free(prompt);
			return (0);
		}
	}
	return (1);
}
