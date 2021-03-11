/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erlajoua <erlajoua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 20:19:29 by erlajoua          #+#    #+#             */
/*   Updated: 2021/03/11 13:25:18 by erlajoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		main_ret(t_cmd *cmd)
{
	if (g_sig > 2)
		return (g_sig);
	if (cmd->exit_status[0] == 1)
		return (cmd->exit_status[1]);
	return (0);
}

void	init_main(t_cmd *cmd, int *ret)
{
	g_sig = 0;
	cmd->exit_status[0] = 0;
	cmd->parent = 1;
	cmd->isforking = 0;
	*ret = 0;
}

int		main(int ret, char **av, char **envp)
{
	char		*prompt;
	t_list		*envs;
	t_cmd		cmd;

	(void)av;
	init_main(&cmd, &ret);
	if (!(envs = init_list_env(envp)))
		return (-1);
	signal_handle();
	display_prompt();
	while ((ret = get_next_line(0, &prompt, 0)) > 0)
	{
		if (prompt[0] != '\0' && main_loop(prompt, &cmd, &envs) == -1)
		{
			get_next_line(666, NULL, 1);
			break ;
		}
		condition_display(cmd.parent, prompt);
		free(prompt);
	}
	free(prompt);
	ft_lstclear(&envs, free);
	ret == 0 ? ft_putstr_fd("exit\n", STDERR_FILENO) : 0;
	return (main_ret(&cmd));
}
