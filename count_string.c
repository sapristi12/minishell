/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_string.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erlajoua <erlajoua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 18:16:30 by erlajoua          #+#    #+#             */
/*   Updated: 2021/03/01 18:16:31 by erlajoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		count_string2(char **cmds, char *str, int *tab)
{
	int		i;
	int		count;

	count = 0;
	i = 0;
	while (cmds[i] && ft_strcmp(cmds[i], "|"))
	{
		if ((!ft_strcmp(cmds[i], str)) && tab[i] == 1)
			count++;
		i++;
	}
	return (count);
}

int		count_string(char **cmds, char *str)
{
	int		i;
	int		count;

	count = 0;
	i = 0;
	while (cmds[i])
	{
		if (!ft_strcmp(cmds[i], str))
			count++;
		i++;
	}
	return (count);
}
