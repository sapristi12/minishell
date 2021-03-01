/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_escape_token.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erlajoua <erlajoua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 18:09:37 by erlajoua          #+#    #+#             */
/*   Updated: 2021/03/01 18:09:48 by erlajoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		*remove_escaped_token(char *str)
{
	int		i;
	char	*tmp;

	i = 0;
	while (str[i] && !is_token_char(str[i]))
		i++;
	if (!str[i])
		return (ft_strdup(str));
	tmp = malloc(1);
	if (!tmp)
		return (NULL);
	tmp[0] = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == SLASH && is_token_char(str[i + 1]))
		{
			tmp = char_strjoin(tmp, str[i + 1]);
			i++;
		}
		else
			tmp = char_strjoin(tmp, str[i]);
		i++;
	}
	return (tmp);
}
