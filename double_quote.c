/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erlajoua <erlajoua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 18:58:42 by erlajoua          #+#    #+#             */
/*   Updated: 2021/03/11 16:22:16 by erlajoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		is_escaped(char c)
{
	if (c == '$')
		return (1);
	if (c == SLASH)
		return (1);
	if (c == D_QUOTE)
		return (1);
	return (0);
}

int				double_dollar(char *str, char **new, t_list **envs)
{
	char	*copy;
	int		i;

	copy = get_var_dollar(str, envs);
	*new = ft_strjoin(*new, copy);
	free(copy);
	i = 0;
	if (is_num(str[i]))
		i++;
	else
	{
		while (str[i] && str[i] != S_QUOTE && str[i] != D_QUOTE
		&& str[i] != ' ' && str[i] != SLASH && str[i] != '@'
		&& str[i] != '=' && str[i] != '?' && str[i] != '/')
			i++;
	}
	if (i == 0 && str[i] == '?')
		return (1);
	return (i);
}

int				next_dollar(char c)
{
	if (c == SLASH)
		return (1);
	if (c == '%')
		return (1);
	if (c == '/')
		return (1);
	if (c == ':')
		return (1);
	return (0);
}

char			*double_quote(char *str, t_list **envs)
{
	char	*new;
	int		i;
	int		max;

	max = ft_strlen(str) - 1;
	i = 0;
	new = ft_strdup("");
	if (!new)
		return (NULL);
	while (str[i] && str[i] != D_QUOTE)
	{
		if (i < max && str[i] == SLASH && is_escaped(str[i + 1]))
			i += normal_slash(&new, str[i + 1]);
		else if (str[i] == '$' && next_dollar(str[i + 1]))
			i += normal_slash(&new, str[i]) - 1;
		else if (str[i] == '$' && max > 0)
			i += double_dollar(&str[i + 1], &new, envs);
		else
			new = char_strjoin(new, str[i]);
		i++;
	}
	return (new);
}
