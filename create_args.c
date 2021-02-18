#include "minishell.h"

int		is_symbol(char *str)
{
	int		i;
	char	**symbols;

	symbols = (char *[4]){">>", ">", "<", "|"};
	i = 0;
	while (i < 4)
	{
		if (!ft_strcmp(str, symbols[i]))
			return (1);
		i++;
	}
	return (0);
}

char	**free_return(char **dest)
{
	free(dest);
	return (NULL);
}

char	**create_package(char **cmds, t_list **envs, int option, int *tab)
{
	char	**dest;
	int		i;

	i = 0;
	while (cmds[i] && (!is_symbol(cmds[i]) || (is_symbol(cmds[i]) && tab[i] == 0)) && ft_strcmp(cmds[i], "|"))
		i++;
	dest = malloc(sizeof(char *) * (i + 1));
	if (!dest)
		return (NULL);
	dest[i] = NULL;
	i = 0;
	while (cmds[i] && (!is_symbol(cmds[i]) || (is_symbol(cmds[i]) && tab[i] == 0)) && ft_strcmp(cmds[i], "|"))
	{
		if (i == 0 && cmds[i][0] != '/' && !is_builtin(cmds[i]))
		{
			if (!(dest[i] = get_path_command(cmds[i], envs, 1)) && option != 0)
				return (free_return(dest));
		}
		else
			dest[i] = ft_strdup(cmds[i]);
		i++;
	}
	return (dest);
}
