/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erlajoua <erlajoua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 18:12:48 by erlajoua          #+#    #+#             */
/*   Updated: 2021/03/11 13:10:34 by erlajoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		normal_tilde(char *str, char **new, t_list **envs)
{
	char	*copy;
	int		i;

	i = 1;
	copy = get_tilde_path(str, envs);
	if (!copy)
		copy = ft_strdup("");
	*new = ft_strjoin(*new, copy);
	free(copy);
	while (str[i] && str[i] != D_QUOTE && str[i]
	!= S_QUOTE && str[i] != '~')
		i++;
	return (i - 1);
}

int		normal_dollar(char *str, char **new, t_list **envs)
{
	char	*copy;
	int		i;

	i = 0;
	copy = get_var_dollar(str, envs);
	*new = ft_strjoin(*new, copy);
	free(copy);
	if (is_num(str[i]))
		i++;
	else
	{
		while (str[i] && str[i] != S_QUOTE && str[i] != D_QUOTE
		&& str[i] != SLASH && str[i] != '$' && str[i] != ' '
		&& str[i] != '=' && str[i] != '@' && str[i] != '?' && str[i] != '/')
			i++;
	}
	if (i == 0 && str[i] == '?')
		return (1);
	return (i);
}

int		normal_slash(char **new, char c)
{
	*new = char_strjoin(*new, c);
	return (1);
}

char	*normal_quote(char *str, t_list **envs)
{
	char	*new;
	int		i;
	int		max;

	max = ft_strlen(str) - 1;
	i = 0;
	new = ft_strdup("");
	if (!new)
		return (NULL);
	while (str[i] && str[i] != D_QUOTE && str[i] != S_QUOTE)
	{
		if (str[0] == '~' && str[1] != '~')
			i += normal_tilde(&str[i], &new, envs);
		else if (str[i] == SLASH)
			i += normal_slash(&new, str[i + 1]);
		else if (str[i] == '$' && next_dollar(str[i + 1]))
			i += normal_slash(&new, str[i]) - 1;
		else if ((str[i] == '$' && max > 0) && (i < max && (str[i + 1])))
			i += normal_dollar(&str[i + 1], &new, envs);
		else
			new = char_strjoin(new, str[i]);
		i++;
	}
	return (new);
}

char	*simple_quote(char *str)
{
	char	*new;
	int		i;
	int		token;

	token = 0;
	i = 0;
	while (str[i] && str[i] != S_QUOTE)
	{
		if (str[i] == '|')
			token++;
		i++;
	}
	new = malloc(i + token + 1);
	if (!new)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != S_QUOTE)
	{
		new[i] = str[i];
		i++;
	}
	new[i] = '\0';
	return (new);
}
