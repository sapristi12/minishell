#include "minishell.h"

int 	only_zeros(char *str)
{
	int i;

	i = 0;
	while (str[i] && str[i] == '0')
		i++;
	if (str[i] == '\0')
		return (1);
	return (0);
}

int 	ft_exit(t_cmd *cmd, t_list **envs)
{
	int i;

	i = 0;
	cmd->exit_status[0] = 1;
	while (cmd->cmds[i] && !is_symbol(cmd->cmds[i]))
		i++;
	if (i == 1)
	{
		cmd->exit_status[1] = 0;
		return (1);
	}
	if (!(ft_llatoi(cmd->cmds[1])))
	{
		if (only_zeros(cmd->cmds[1]))
		{
			cmd->exit_status[1] = 0;
			return (1);
		}
		ft_putstr_fd("minishell: exit: ", 1);
		ft_putstr_fd(cmd->cmds[1], 1);
		ft_putstr_fd(": numeric argument required\n", 1);
		cmd->exit_status[1] = 2;
		return (1);
	}
	if (i > 2)
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 1);
		cmd->exit_status[1] = 1;
		return (1);
	}
	cmd->exit_status[1] = ft_llatoi(cmd->cmds[1]) % 256;
	return (1);
}
