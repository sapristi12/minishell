/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_return.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erlajoua <erlajoua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 17:49:09 by erlajoua          #+#    #+#             */
/*   Updated: 2021/03/05 11:10:28 by erlajoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		free_end_pipe(t_cmd *cmd, int ret)
{
	int i;
	int j;

	i = 0;
	while (cmd->pipe.all[i])
	{
		j = 0;
		while (cmd->pipe.all[i][j])
		{
			free(cmd->pipe.all[i][j]);
			j++;
		}
		free(cmd->pipe.all[i]);
		i++;
	}
	free(cmd->pipe.all);
	free(cmd->pipe.fd);
	return (ret);
}
