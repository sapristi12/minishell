/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_prompt.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erlajoua <erlajoua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 20:07:14 by erlajoua          #+#    #+#             */
/*   Updated: 2021/03/11 13:00:01 by erlajoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			init_prompt(t_prompt *p)
{
	p->i = 0;
	p->flag = 0;
	p->in_quote = -1;
}

int				multiple_semicolon(char *str)
{
	t_prompt	p;

	init_prompt(&p);
	if (!multiple_semi2(str, &(p.i)))
		return (0);
	while (str[p.i])
	{
		if (str[p.i] == SLASH && (str[p.i + 1] == SLASH ||
		str[p.i + 1] == D_QUOTE
		|| (p.in_quote == -1 && str[p.i + 1] == S_QUOTE)))
			p.i++;
		else if (p.in_quote == 1 && ((p.i > 1 && is_first_condition(p.tmp,
		str[p.i], str[p.i - 1], str[p.i - 2])) || (p.i > 0 &&
		is_first_condition(p.tmp, str[p.i], str[p.i - 1], SLASH))))
			p.in_quote = -(p.in_quote);
		else if (p.in_quote == -1)
		{
			if (str[p.i] == S_QUOTE || str[p.i] == D_QUOTE)
				multiple_semi3(str, p.i, &(p.tmp), &(p.in_quote));
			else if (!multiple_semi1(str, &(p.flag), &(p.i)))
				return (0);
		}
		p.i++;
	}
	return (1);
}

int				check_prompt(int index, char *prompt)
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
