#include "minishell.h"

int 	free_error_redir(t_cmd *cmd, t_list **envs, int ret)
{
	int i;

	i = 0;
	while (cmd->pipe.all[i])
	{
		free_char_double_array(cmd->pipe.all[i]);
		i++;
	}
	ft_lstclear(envs, free);
	free(cmd->pipe.all);
	return (ret);
}
