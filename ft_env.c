#include "minishell.h"

int 	ft_env(t_cmd *cmd, t_list **envs)
{
	int i;

	i = 0;
	while (cmd->cmds[i] && !is_symbol(cmd->cmds[i]))
		i++;
	if (i > 1)
	{
		ft_putstr_fd("env: «", 1);
		ft_putstr_fd(cmd->cmds[1], 1);
		ft_putstr_fd("»: No such file or directory\n", 1);
		return (1);
	}
	ft_afflist(envs);
	return (1);
}
