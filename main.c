/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erlajoua <erlajoua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 20:19:29 by erlajoua          #+#    #+#             */
/*   Updated: 2021/03/10 14:37:00 by erlajoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		check_status(char **cmds, int status)
{
	if (status == -1)
		free_parsing_line(cmds, status);
	if (status == -2)
	{
		free_char_double_array(cmds);
		return (-1);
	}
	return (1);
}

int		free_split_null(char *prompt, char **cmds)
{
	free(prompt);
	free_char_double_array(cmds);
	ft_putstr_fd(
	"minishell: syntax error near unexpected ';'\n"
	, STDERR_FILENO);
	return (0);
}

int		main_loop(char *prompt, t_cmd *cmd, t_list **envs)
{
	int		i;
	int		status;
	char	**cmds;
	int		ret;

	i = 0;
	if (!check_prompt(1, prompt) || !check_prompt(2, prompt))
		return (0);
	if (!(cmds = new_split(prompt, ';')) || cmds[i] == NULL)
		return (free_split_null(prompt, cmds));
	while (cmds[i] && !only_spaces(cmds[i]))
	{
		if (!only_spaces(cmds[i]))
		{
			status = parsing_line(cmds[i], envs, cmd);
			if ((ret = check_status(cmds, status)) <= -1)
			{
				if (ret == -2)
					free(prompt);
				return (-1);
			}
		}
		i++;
	}
	if (cmds[i] && !only_spaces(cmds[i]))
		ft_putstr_fd(
		"minishell: syntax error near unexpected ';'\n", STDERR_FILENO);
	free_char_double_array(cmds);
	return (0);
}

int		main_ret(t_cmd *cmd)
{
	if (g_sig > 2)
		return (g_sig);
	if (cmd->exit_status[0] == 1)
		return (cmd->exit_status[1]);
	return (0);
}

int		main(int ret, char **av, char **envp)
{
	char		*prompt;
	t_list		*envs;
	t_cmd		cmd;

	g_sig = 0;
	(void)av;
	ret = 0;
	cmd.exit_status[0] = 0;
	cmd.parent = 0;
	cmd.isforking = 0;
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
