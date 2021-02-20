#include "minishell.h"

int		count_string2(char **cmds, char *str, int *tab)
{
	int		i;
	int		count;

	count = 0;
	i = 0;
	while (cmds[i] && ft_strcmp(cmds[i], "|"))
	{
		if ((!ft_strcmp(cmds[i], str)) && tab[i] == 1)
			count++;
		i++;
	}
	return (count);
}

int		count_string(char **cmds, char *str)
{
	int		i;
	int		count;

	count = 0;
	i = 0;
	while (cmds[i])
	{
		if (!ft_strcmp(cmds[i], str))
			count++;
		i++;
	}
	return (count);
}
