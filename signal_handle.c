/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handle.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erlajoua <erlajoua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 17:52:50 by erlajoua          #+#    #+#             */
/*   Updated: 2021/03/01 18:07:39 by erlajoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	signal_int(int signo)
{
	if (signo == SIGINT)
	{
		ft_putstr_fd("\n", 1);
		display_prompt();
	}
	g_sig = 128 + signo;
}

void	signal_quit(int signo)
{
	if (signo == SIGQUIT)
	{
		ft_putstr_fd("Quit : (core dumped)\n", 1);
		display_prompt();
	}
	g_sig = 128 + signo;
}

void	signal_handle(void)
{
	signal(SIGINT, signal_int);
	signal(SIGQUIT, signal_quit);
}
