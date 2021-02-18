#include "minishell.h"

char    *get_left(t_cmd *cmd, int index)
{
	int		i;
	int		j;
	char 	**strs;

	strs = pointer_package(cmd->cmds, index);
	j = 0;
	i = 0;
	while (strs[i + 1] && ft_strcmp(strs[i + 1], "|"))
	{
		if (!ft_strcmp(strs[i], "<") && cmd->tab[index][i] == 1)
		{
			j++;
			if (j == cmd->redir.left)
				return (strs[i + 1]);
		}
		i++;
	}
	return (NULL);
}

char    *get_right(t_cmd *cmd, int index)
{
	int		i;
	int		j;
	char 	**strs;

	strs = pointer_package(cmd->cmds, index);
	j = 0;
	i = 0;
	while (strs[i + 1] && ft_strcmp(strs[i + 1], "|"))
	{
		if ((!ft_strcmp(strs[i], ">>") || (!ft_strcmp(strs[i], ">")) && cmd->tab[index][i] == 1))
		{
			j++;
			if (j == cmd->redir.right)
			{
				if (!ft_strcmp(strs[i], ">>"))
					cmd->redir.mode = 'A';
				else
					cmd->redir.mode = 'T';
				return (strs[i + 1]);
			}
		}
		i++;
	}
	return (NULL);
}