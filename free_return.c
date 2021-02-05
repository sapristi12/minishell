#include "minishell.h"

int 	free_end_pipe(t_cmd *cmd, int ret)
{
	int i;
	int j;

	i = 0;
	while (cmd->pipe.all[i])
	{
		j = 0;
		while (cmd->pipe.all[i][j])
		{
			free(cmd->pipe.all[i][j]);
			j++;
		}
		free(cmd->pipe.all[i]);
		i++;
	}
	free(cmd->pipe.all);
	free(cmd->pipe.fd);
	return (ret);
}

