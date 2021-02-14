#include "minishell.h"

int 	ft_echo(t_cmd *cmd)
{
	int i;
	int size;
	int flag;

	size = 1;
	flag = 0;
	i = 1;
	while (cmd->cmds[size] && !is_symbol(cmd->cmds[size]))
		size++;
	if (!ft_strcmp(cmd->cmds[1], "-n"))
	{
		flag = 1;
		i++;
	}
	while (i < size)
	{
		ft_putstr_fd(cmd->cmds[i], 1);
		if (i != size - 1)
			ft_putstr_fd(" ", 1);
		i++;
	}
	if (flag == 0 || size < 2)
		ft_putstr_fd("\n", 1);
	return (1);
}
