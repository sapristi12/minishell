/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erlajoua <erlajoua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 17:47:02 by erlajoua          #+#    #+#             */
/*   Updated: 2021/03/11 12:12:08 by erlajoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_echo(t_cmd *cmd, int index)
{
	int		i;
	int		size;
	int		flag;
	char	**strs;

	strs = pointer_package(cmd->cmds, index);
	size = 1;
	flag = 0;
	i = 1;
	while (strs[size] && (!is_symbol(strs[size]) || (ft_strcmp(strs[size],
	"|") && (is_symbol(strs[size]) && cmd->tab[index][size] == 0))))
		size++;
	while (strs[i] && !ft_strcmp(strs[i], "-n") && i++)
		flag = 1;
	while (i < size)
	{
		ft_putstr_fd(strs[i], 1);
		if (i != size - 1)
			ft_putstr_fd(" ", STDOUT_FILENO);
		i++;
	}
	if (flag == 0 || size < 2)
		ft_putstr_fd("\n", STDOUT_FILENO);
	return (1);
}
