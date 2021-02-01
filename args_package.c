#include "minishell.h"

static int		move_pointer(char **cmds)
{
	int i;

	i = 0;
	while (cmds[i] && ft_strcmp(cmds[i], "|"))
		i++;
	return (i + 1);
}

static char		**get_arg(char **cmds)
{
	int		i;
	int		j;
	char	**args;

	j = 0;
	i = 0;
	while (cmds[i] && ft_strcmp(cmds[i], "|"))
		i++;
	args = malloc(sizeof(char *) * i);
	if (!args)
		return (NULL);
	args[i] = NULL;
	i = 0;
	while (cmds[i] && ft_strcmp(cmds[i], "|"))
	{
		args[i] = ft_strdup(cmds[i]);
		i++;
	}
	return (args);
}
