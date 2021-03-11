/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_even_quote.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erlajoua <erlajoua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 20:25:37 by erlajoua          #+#    #+#             */
/*   Updated: 2021/03/11 13:01:19 by erlajoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			apply_tmp(char *tmp, char c, int *in_quote)
{
	*tmp = c;
	*in_quote = *(in_quote) * -1;
}

static int		is_first_condition_q(char tmp, char now, char bef, char bef2)
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

int				is_even_quote(char *str)
{
	int		in_quote;
	int		i;
	char	tmp;

	i = 0;
	in_quote = -1;
	while (str[i])
	{
		if (str[i] == SLASH && (str[i + 1] == SLASH
		|| str[i + 1] == D_QUOTE || (in_quote == -1 && str[i + 1] == S_QUOTE)))
			i++;
		else if (in_quote == 1 && ((i > 1 && is_first_condition_q(tmp, str[i],
		str[i - 1], str[i - 2])) || (i > 0 && is_first_condition_q(tmp, str[i],
		str[i - 1], SLASH))))
			in_quote = -in_quote;
		else if (in_quote == -1)
			if (str[i] == S_QUOTE || str[i] == D_QUOTE)
				if ((i > 0 && is_second_condition(str[i], str[i - 1], i))
				|| (i == 0 && is_second_condition(str[i], 0, i)))
					apply_tmp(&tmp, str[i], &in_quote);
		i++;
	}
	if (in_quote == -1)
		return (1);
	return (0);
}
