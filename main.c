#include "minishell.h"

int 	multiple_semicolon(char *str)
{
	int i;

	i = 0;
	if (str[0] == ';')
		return (0);
	while (str[i + 1])
	{
		if (str[i] == ';' && str[i + 1] == ';')
			return (0);
		if (str[i] == ';')
		{
			i++;
			while (str[i] && str[i] == ' ')
				i++;
			if (str[i] == ';')
				return (0);
		}
		i++;
	}
	return (1);
}

int 	check_prompt(int index, char *prompt)
{
	if (index == 1)
	{
		if (only_spaces(prompt))
		{
			free(prompt);
			return (0);
		}
	}
	else if (index == 2)
	{
		if (!multiple_semicolon(prompt))
		{
			ft_putstr_fd("minishell: syntax error near unexpected ';'\n", 1);
			free(prompt);
			return (0);
		}
	}
	return (1);
}

int 	check_status(char **cmds, char *prompt, int status)
{
	if (status == -1)
		free_parsing_line(cmds, prompt, status);
	if (status == -2)
	{
		free_char_double_array(cmds);
		return (-1);
	}
	return (1);
}

int 	free_split_null(char *prompt, char **cmds)
{

	free(prompt);
	free_char_double_array(cmds);
	ft_putstr_fd("minishell: syntax error near unexpected ';'\n", 1);
	return (0);
}

int		main_loop(char *prompt, t_cmd *cmd, t_list **envs)
{
	int		i;
	int		status;
	char	**cmds;

	i = 0;
	if (!check_prompt(1, prompt) || !check_prompt(2, prompt))
		return (0);
	cmds = new_split(prompt, ';');
	if (cmds == NULL || cmds[i] == NULL)
		return (free_split_null(prompt, cmds));
	while (cmds[i] && !only_spaces(cmds[i]))
	{
		if (!only_spaces(cmds[i]))
		{
			status = parsing_line(cmds[i], envs, cmd);
			if (check_status(cmds, prompt, status) == -1)
				return (-1);
		}
		i++;
	}
	if (cmds[i] && !only_spaces(cmds[i]))
		ft_putstr_fd("minishell: syntax error near unexpected ';'\n", 1);
	free(prompt);
	free_char_double_array(cmds);
	return (0);
}

int 	main_ret(t_cmd *cmd)
{
	if (g_sig > 2)
		return (g_sig);
	if (cmd->exit_status[0] == 1)
		return (cmd->exit_status[1]);
	return (0);
}

int		main(int i, char **av, char **envp)
{
	char	*prompt;
	t_list	*envs;
	t_cmd	cmd;

	g_sig = 0;
	(void)av;
	i = 0;
	if (!(envs = init_list_env(envp)))
		return (-1);
	signal_handle();
	display_prompt();
	while (get_next_line(0, &prompt, 0) > 0)
	{
		if (prompt[0] != '\0' && main_loop(prompt, &cmd, &envs) == -1)
		{
			get_next_line(666, NULL, 1);
			break;
		}
		if (g_sig <= 2 || g_sig == 127)
			display_prompt();
	}
	free(prompt);
	ft_lstclear(&envs, free);
	return (main_ret(&cmd));
}
