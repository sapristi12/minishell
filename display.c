/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erlajoua <erlajoua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 18:58:12 by erlajoua          #+#    #+#             */
/*   Updated: 2021/03/11 21:55:48 by erlajoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	condition_display(t_cmd *cmd, char *prompt)
{
	int parent;

	(void)cmd;
	parent = get_flag(GET, 0);
	//printf("==parent in display : %d g_sig : %d\n", parent, g_sig);
	if ((prompt[0] == 0 || parent == 0))
	{
		if (g_sig <= 2 || g_sig == 127 || g_sig == 16
		|| prompt[0] == 0 || g_sig == 126)
			display_prompt();
	}
	else if ((g_sig == 0 || g_sig == 127 || g_sig == 126)
	&& parent == 0)
	{
		display_prompt();
	}
}

void	ft_putstr_fd(char *str, int fd)
{
	write(fd, str, ft_strlen(str));
}

void	display_prompt(void)
{
	ft_putstr_fd("minishell $>", STDOUT_FILENO);
}
