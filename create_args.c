#include "minishell.h"

static int 		is_symbol(char *str)
{
	int		i;
	char 	**symbols;

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

char 			**create_package(char **cmds, t_list *envs)
{
	char	**dest;
	int 	size;
	int 	i;

	i = 0;
	size = 0;
	while (cmds[size] && !is_symbol(cmds[size]))
		size++;
	dest = malloc(sizeof(char *) * size + 1);
	if (!dest)
		return (NULL);
	dest[size] = NULL;
	while (i < size)
	{
		if (i == 0 && cmds[i][0] != '/')
			dest[i] = get_path_command(cmds[i], envs);
		else
			dest[i] = ft_strdup(cmds[i]);
		i++;
	}
	return (dest);
}
