/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_condition.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erlajoua <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 12:57:12 by erlajoua          #+#    #+#             */
/*   Updated: 2021/03/11 13:02:12 by erlajoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int				is_first_condition(char tmp, char now, char bef, char bef2)
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

void			multiple_semi3(char *str, int i, char *tmp, int *in_quote)
{
	if ((i > 0 && is_second_condition(str[i], str[i - 1], i))
		|| (i == 0 && is_second_condition(str[i], 0, i)))
		apply_tmp(tmp, str[i], in_quote);
}

int				multiple_semi2(char *str, int *j)
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
