#include "minishell.h"

int     main_loop(char *prompt, char **envp)
{
    int     i;
    char    **cmds;

    i = 0;
    cmds = new_split(prompt, ';');
    if (!cmds)
        return (-1);
    while (cmds[i])
    {
        if (parsing_line(cmds[i], envp) == -1)
            return (free_parsing_line(cmds, prompt));
        i++;
    }
    free(prompt);
    free_char_double_array(cmds);
}

int		main(int i, char **av, char **envp)
{
	char	*prompt;
	char    **cmds;

    (void)av;
	i = 0;
	display_prompt();
	while (get_next_line(0, &prompt, 0))
	{
	    if (main_loop(prompt, envp) == -1)
	        return (-1); //let's see later
        display_prompt();
	}
	free(prompt);
	return (0);
}
