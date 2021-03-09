/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_prompt.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erlajoua <erlajoua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 20:07:14 by erlajoua          #+#    #+#             */
/*   Updated: 2021/03/09 20:18:25 by erlajoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*int		check_semicolon(char *str)
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
}*/

static int		is_first_condition(char tmp, char now, char bef, char bef2)
{
	if ((now == tmp && tmp == S_QUOTE))
		return (1);
	if (tmp == D_QUOTE && now == tmp)
	{
		if ((bef != SLASH) || (bef2 == SLASH && bef == SLASH))
			return (1);
	}
	return (0);
}

static int		is_second_condition(char now, char bef, int i)
{
	if (now == S_QUOTE)
		return (1);
	if ((i > 0 && (now == D_QUOTE && bef != SLASH))
	|| (i == 0 && now == D_QUOTE))
		return (1);
	return (0);
}

int		multiple_semicolon(char *str)
{
	int		i;
	int		in_quote;
	int		flag;
	char	tmp;

	flag = 0;
	in_quote = -1;
	i = 0;
	if (str[i] == ' ')
	{
		while (str[i] == ' ')
			i++;
		if (str[i] == ';')
			return (0);
	}
	while (str[i + 1])
	{
		if (str[i] == SLASH && (str[i + 1] == SLASH || str[i + 1] == D_QUOTE || (in_quote == -1 && str[i + 1] == S_QUOTE)))
			i++;
		else if (in_quote == 1 && ((i > 1 && is_first_condition(tmp, str[i], str[i - 1], str[i - 2])) || (i > 0 && is_first_condition(tmp, str[i], str[i - 1], SLASH))))
			in_quote = -in_quote;
		else if (in_quote == -1)
		{
			if (str[i] == S_QUOTE || str[i] == D_QUOTE)
			{
				if ((i > 0 && is_second_condition(str[i], str[i - 1], i))
					|| (i == 0 && is_second_condition(str[i], 0, i)))
					apply_tmp(&tmp, str[i], &in_quote);
			}
			else
			{
				if (str[i] == ';' && flag == 0)
					flag = 1;
				else if (str[i] == ';' && flag == 1)
					return (0);
				if (str[i] == ' ')
				{
					while (str[i] && str[i] == ' ')
						i++;
					i--;
				}
			}
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
			return (0);
	}
	else if (index == 2)
	{
		if (!multiple_semicolon(prompt))
		{
			ft_putstr_fd(
			"minishell: syntax error near unexpected ';'\n", STDERR_FILENO);
			return (0);
		}
	}
	return (1);
}
