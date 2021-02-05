#include "minishell.h"

int 	ft_env(t_cmd *cmd, t_list **envs)
{
	(void)cmd;
	ft_afflist(envs);
	return (1);
}
