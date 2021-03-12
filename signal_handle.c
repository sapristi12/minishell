/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handle.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erlajoua <erlajoua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 17:52:50 by erlajoua          #+#    #+#             */
/*   Updated: 2021/03/12 09:13:29 by erlajoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		get_flag(int op, int val)
{
	static int	flag;

	if (op == 1)
		flag = val;
	return (flag);
}

int		get_dup(int op, int val)
{
	static int fd;

	if (op == 1)
		fd = val;
	return (fd);
}

void	signal_int(int signo)
{
	ft_putstr_fd("\n", STDERR_FILENO);
	if (get_flag(GET, 0) == 1)
		return ;
	if (signo == SIGINT)
	{
		dup2(get_dup(GET, 0), STDOUT_FILENO);
		display_prompt();
	}
	g_sig = 128 + signo;
}

void	signal_quit(int signo)
{
	if (get_flag(GET, 0) != 1)
	{
		ft_putstr_fd("\b\b  \b\b", STDOUT_FILENO);
		return ;
	}
	if (signo == SIGQUIT)
	{
		ft_putstr_fd("Quit : (core dumped)\n", STDERR_FILENO);
		dup2(get_dup(GET, 0), STDOUT_FILENO);
		display_prompt();
	}
	g_sig = 128 + signo;
}

void	signal_handle(void)
{
	signal(SIGINT, signal_int);
	signal(SIGQUIT, signal_quit);
}
