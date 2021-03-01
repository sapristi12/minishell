/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_errno.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erlajoua <erlajoua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 17:46:40 by erlajoua          #+#    #+#             */
/*   Updated: 2021/03/01 20:19:13 by erlajoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		errno_index(int index)
{
	if (index == -1)
		ft_putstr_fd("Error: parsing quotes\n", 1);
	if (index == -2)
		ft_putstr_fd("Error: malloc failed create_space_around\n", 1);
	if (index == -3)
		ft_putstr_fd("Error: parsing line malloc split failed\n", 1);
	if (index == -4)
		ft_putstr_fd("minishell: syntax error near unexpected 'newline'\n", 1);
	if (index == -5)
		ft_putstr_fd("minishell: parsing line error pipes\n", 1);
	if (index == -6)
		ft_putstr_fd("minishell: syntax error near unexpected 'newline'\n", 1);
	if (index == -7)
		ft_putstr_fd("Error: parsing line malloc envs failed\n", 1);
	return (-1);
}

static int		errno_parsing_command(void)
{
	return (-1);
}

int				errno_parsing_line(int index)
{
	g_sig = 2;
	if (index >= -9 && index <= -1)
		return (errno_index(index));
	if (index >= -19 && index <= -11)
		return (errno_parsing_command());
	return (-1);
}
