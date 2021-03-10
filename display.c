/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erlajoua <erlajoua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 18:58:35 by erlajoua          #+#    #+#             */
/*   Updated: 2021/03/10 16:51:59 by erlajoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	condition_display(int parent, char *prompt)
{
	if (prompt[0] == 0 || parent == 1)
	{
		if (g_sig <= 2 || g_sig == 127 || g_sig == 16 || prompt[0] == 0)
			display_prompt();
	}
	else if (g_sig == 0 && parent == 0)
		display_prompt();
}

void	ft_putstr_fd(char *str, int fd)
{
	write(fd, str, ft_strlen(str));
}

void	display_prompt(void)
{
	ft_putstr_fd("minishell $>", 1);
}
