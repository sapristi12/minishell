/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_prompt.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erlajoua <erlajoua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 20:07:14 by erlajoua          #+#    #+#             */
/*   Updated: 2021/03/10 15:37:16 by erlajoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int 			multiple_semi2(char *str, int *j)
{
	int i;

	i = *j;
	if (str[i] == ' ' || str[i] == ';')
	{
		while (str[i] && str[i] == ' ')
			i++;
		if (str[i] == ';')
			return (0);
	}
	*j = i;
	return (1);
}

int				multiple_semi1(char *str, int *flag, int *j)
{
	int i;

	i = *j;
	if (str[i] == ';' && *flag == 0)
		*flag = 1;
	else if (str[i] == ';' && *flag == 1)
		return (0);
	else if (str[i + 1] != ' ' && str[i] != ';')
		*flag = 0;
	if (str[i] == ';' && str[i + 1] == ' ')
	{
		i++;
		while (str[i] && str[i] == ' ')
			i++;
		i--;
	}
	*j = i;
	return (1);
}

void 			multiple_semi3(char *str, int i, char *tmp, int *in_quote)
{
	if ((i > 0 && is_second_condition(str[i], str[i - 1], i))
		|| (i == 0 && is_second_condition(str[i], 0, i)))
		apply_tmp(tmp, str[i], in_quote);
}

void 	init_prompt(t_prompt *p)
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
		if (str[p.i] == SLASH && (str[p.i + 1] == SLASH || str[p.i + 1] == D_QUOTE || (p.in_quote == -1 && str[p.i + 1] == S_QUOTE)))
			p.i++;
		else if (p.in_quote == 1 && ((p.i > 1 && is_first_condition(p.tmp, str[p.i], str[p.i - 1],str[p.i - 2])) || (p.i > 0 && is_first_condition(p.tmp, str[p.i], str[p.i - 1], SLASH))))
			p.in_quote = -(p.in_quote);
		else if (p.in_quote == -1)
		{
			if (str[p.i] == S_QUOTE || str[p.i] == D_QUOTE)
				multiple_semi3(str, p.i, &(p.tmp), &(p.in_quote));
			else if (!multiple_semi1(str, &(p.flag), &(p.i)))
					return (0);
		}
		i++;
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
