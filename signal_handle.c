/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handle.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erlajoua <erlajoua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 17:52:50 by erlajoua          #+#    #+#             */
/*   Updated: 2021/03/10 14:31:33 by erlajoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		get_pid(int op, int val)
{
	static int	pid;

	if (op == 1)
		pid = val;
	return (pid);
}

void	signal_int(int signo)
{
	if (signo == SIGINT)
	{
		ft_putstr_fd("\n", STDERR_FILENO);
		display_prompt();
	}
	g_sig = 128 + signo;
}

void	signal_quit(int signo)
{
	if (get_pid(GET, 0) == 0)
	{
		ft_putstr_fd("\b\b  \b\b", STDOUT_FILENO);
		return ;
	}
	if (signo == SIGQUIT)
	{
		ft_putstr_fd("Quit : (core dumped)\n", STDERR_FILENO);
		display_prompt();
	}
	g_sig = 128 + signo;
}

void	signal_handle(void)
{
	signal(SIGINT, signal_int);
	signal(SIGQUIT, signal_quit);
}
