#include "minishell.h"

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
