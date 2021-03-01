/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erlajoua <erlajoua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 18:16:27 by erlajoua          #+#    #+#             */
/*   Updated: 2021/03/01 18:16:28 by erlajoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_after(t_cmd *cmd, int index)
{
	close(cmd->pipe.fd[index - 1][0]);
	close(cmd->pipe.fd[index][1]);
}

void	close_last(int index, int n, int (*fd)[2])
{
	int i;
	int j;

	index = 0;
	i = 0;
	n++;
	while (i < n)
	{
		j = 0;
		while (j < 2)
		{
			if (i != 1 || j != 0)
				close(fd[i][j]);
			j++;
		}
		i++;
	}
}

void	close_first(int index, int n, int (*fd)[2])
{
	int i;
	int j;

	i = 0;
	index = 0;
	n++;
	while (i < n)
	{
		j = 0;
		while (j < 2)
		{
			if (i != 0 || j != 1)
				close(fd[i][j]);
			j++;
		}
		i++;
	}
}

void	close_all(int index, int n, int (*fd)[2])
{
	int i;
	int j;

	i = 0;
	n++;
	while (i < n)
	{
		j = 0;
		while (j < 2)
		{
			if ((i != index || j != 0) && (i != index + 1 || j != 1))
				close(fd[i][j]);
			j++;
		}
		i++;
	}
}
