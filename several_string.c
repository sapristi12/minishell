/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   several_string.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erlajoua <erlajoua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 18:07:43 by erlajoua          #+#    #+#             */
/*   Updated: 2021/03/11 13:20:41 by erlajoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		several_string(char **cmds)
{
	int		i;
	int		j;
	int		k;
	char	**strs;

	strs = (char *[5]){">", ">>", "<", "|", NULL};
	i = 0;
	while (cmds[i + 1] && ft_strcmp(cmds[0], "|"))
	{
		j = -1;
		while (++j < 4)
		{
			if (!ft_strcmp(cmds[i], strs[j]))
			{
				k = -1;
				while (++k < 4)
				{
					if (!ft_strcmp(cmds[i + 1], strs[k]))
						return (0);
				}
			}
		}
		i++;
	}
	return (!ft_strcmp(cmds[i], "|")) ? 0 : 1;
}
