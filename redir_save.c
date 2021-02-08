#include "minishell.h"

char    *get_left(t_cmd *cmd)
{
	int i;
	int j;

	j = 0;
	i = 0;
	while (cmd->cmds[i + 1] && ft_strcmp(cmd->cmds[i + 1], "|"))
	{
		if (!ft_strcmp(cmd->cmds[i], "<"))
		{
			j++;
			if (j == cmd->redir.left)
				return (cmd->cmds[i + 1]);
		}
		i++;
	}
	return (NULL);
}

char    *get_right(t_cmd *cmd)
{
	int i;
	int j;

	j = 0;
	i = 0;
	while (cmd->cmds[i + 1] && ft_strcmp(cmd->cmds[i + 1], "|"))
	{
		if (!ft_strcmp(cmd->cmds[i], ">>") || !ft_strcmp(cmd->cmds[i], ">"))
		{
			j++;
			if (j == cmd->redir.right)
			{
				if (!ft_strcmp(cmd->cmds[i], ">>"))
					cmd->redir.mode = 'A';
				else
					cmd->redir.mode = 'T';
				return (cmd->cmds[i + 1]);
			}
		}
		i++;
	}
	return (NULL);
}