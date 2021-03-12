/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erlajoua <erlajoua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 15:15:12 by erlajoua          #+#    #+#             */
/*   Updated: 2021/03/12 13:11:42 by erlajoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			hub_join_not_found(char *cmd)
{
	char	*dest;

	if (!(dest = ft_strdup("")))
		return ;
	dest = ft_strjoin(dest, cmd);
	dest = ft_strjoin(dest, " : command not found\n");
	ft_putstr_fd(dest, STDERR_FILENO);
	free(dest);
}

char			*char_strjoin(char *str, char c)
{
	char	*new;
	int		i;

	if (!(new = malloc(ft_strlen(str) + 2)))
		return (NULL);
	i = 0;
	while (i < ft_strlen(str))
	{
		new[i] = str[i];
		++i;
	}
	new[i++] = c;
	new[i] = 0;
	free(str);
	return (new);
}
