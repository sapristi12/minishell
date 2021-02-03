#include "minishell.h"

int		main_loop(char *prompt, t_list **envs)
{
	int		i;
	int		status;
	char	**cmds;

	i = 0;
	cmds = new_split(prompt, ';');
	if (!cmds)
		return (-1);
	while (cmds[i])
	{
		status = parsing_line(cmds[i], envs);
		if (status < 0)
			free_parsing_line(cmds, prompt, status);
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

	(void)av;
	i = 0;
	if (!(envs = init_list_env(envp)))
		return (-1);
	display_prompt();
	while (get_next_line(0, &prompt, 0))
	{
		main_loop(prompt, &envs);
		display_prompt();
	}
	printf("sortie\n");
	free(prompt);
	ft_lstclear(&envs, free);
	return (0);
}
