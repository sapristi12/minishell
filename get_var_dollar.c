/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_var_dollar.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erlajoua <erlajoua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 20:34:22 by erlajoua          #+#    #+#             */
/*   Updated: 2021/03/10 20:05:01 by erlajoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*exit_package(char *name)
{
	int		size;
	int		nb;
	char	*str;

	nb = g_sig;
	size = 0;
	if (nb == 0)
		size = 1;
	while (nb != 0)
	{
		nb /= 10;
		size++;
	}
	str = malloc(size + 1);
	if (!str)
		return (NULL);
	str[size] = 0;
	nb = g_sig;
	while (size-- > 0)
	{
		str[size] = (nb % 10) + 48;
		nb /= 10;
	}
	free(name);
	return (str);
}

int		condition_dollar(char c)
{
	if (!c)
		return (0);
	if (c == S_QUOTE || c == D_QUOTE)
		return (0);
	if (c == SLASH || c == '$')
		return (0);
	if (c == ' ' || c == '@')
		return (0);
	if (c == '=' || c == '?')
		return (0);
	if (c == '/')
		return (0);
	return (1);
}

char	*get_var_dollar(char *str, t_list **envs)
{
	int		i;
	char	*name;
	char	*tmp;

	i = 0;
	name = deux_strdup("");
	if (!name)
		return (NULL);
	if (is_num(str[i]))
	{
		name = char_strjoin(name, str[i]);
		i++;
	}
	else
	{
		while (condition_dollar(str[i]))
			i++;
	}
	i = 0;
	if (is_num(str[i]))
	{
		name = char_strjoin(name, str[i]);
		i++;
	}
	else
	{
		while (condition_dollar(str[i]))
		{
			name[i] = str[i];
			i++;
		}
	}
	if (i == 0 && str[i] == '?')
		return (exit_package(name));
	tmp = get_env(*envs, name);
	free(name);
	if (tmp)
		return (ft_strdup(tmp));
	return (ft_strdup(""));
}
