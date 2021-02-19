#include "minishell.h"

int		main_loop(char *prompt, t_cmd *cmd, t_list **envs)
{
	int		i;
	int		status;
	char	**cmds;

	i = 0;
	cmds = new_split(prompt, ';');
	if (cmds == NULL || cmds[i] == NULL)
		return (-1);
	while (cmds[i])
	{
		status = parsing_line(cmds[i], envs, cmd);
		if (status == -1)
			free_parsing_line(cmds, prompt, status);
		if (status == -2)
		{
			free_char_double_array(cmds);
			return (-1);
		}
		i++;
	}
	free(prompt);
	free_char_double_array(cmds);
	return (0);
}

int		main(int i, char **av, char **envp)
{
	char	*prompt;
	t_list	*envs;
	t_cmd	cmd;
	int 	ret;

	(void)av;
	i = 0;
	g_sig = 0;
	if (!(envs = init_list_env(envp)))
		return (-1);
	signal_handle();
	display_prompt();
	while ((ret = get_next_line(0, &prompt, 0)) > 0)
	{
		if (prompt[0] != '\0' && main_loop(prompt, &cmd, &envs) == -1)
		{
			get_next_line(666, NULL, 1);
			break;
		}
		display_prompt();
	}
	free(prompt);
	ft_lstclear(&envs, free);
	if (g_sig != 0)
		return (g_sig);
	if (cmd.exit_status[0] == 1)
		return (cmd.exit_status[1]);
	return (0);
}
