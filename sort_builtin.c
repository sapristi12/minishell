#include "minishell.h"

int 	sort_builtin(t_cmd *cmd, t_list **envs)
{
	if (!ft_strcmp(cmd->cmds[0], "pwd"))
		ft_pwd(cmd);
	if (!ft_strcmp(cmd->cmds[0], "cd"))
		ft_cd(cmd, envs);
	if (!ft_strcmp(cmd->cmds[0], "env"))
		ft_env(cmd, envs);
	if (!(ft_strcmp(cmd->cmds[0], "unset")))
		ft_unset(cmd, envs);
	return (1);
}
