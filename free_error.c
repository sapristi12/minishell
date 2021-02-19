#include "minishell.h"

void 	free_int_double_array(t_cmd *cmd)
{
	int i;

	i = 0;
	while (i < cmd->pipe.nb_pipe + 1)
	{
		free(cmd->tab[i]);
		i++;
	}
	free(cmd->tab);
}

int 	free_error_redir(t_cmd *cmd, t_list **envs, int ret)
{
	int i;

	i = 0;
	while (cmd->pipe.all[i])
	{
		free_char_double_array(cmd->pipe.all[i]);
		i++;
	}
	free(cmd->pipe.all);
	return (ret);
}
