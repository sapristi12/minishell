#include "minishell.h"

int		main(int i, char **av, char **envp)
{
	char	*prompt;
	int		ret;

	i = 0;
	while (get_next_line(0, &prompt, 0))
	{
		av = new_split(prompt, ';');
		if (!av)
		    return (-1);
		i = 0;
		while (av[i])
		{
			if (parsing_line(av[i], envp) == -1)
			    return (free_parsing_line(av, prompt));
			i++;
		}
		free(prompt);
	}
	free(prompt);
	return (0);
}