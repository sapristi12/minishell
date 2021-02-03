#include "minishell.h"

static int		basic_first_command(char **cmds, t_list **envs)
{
	char		**args;

	if (is_builtin(cmds[0]))
		return (1);
	if (!(args = create_package(cmds, envs)))
	{
		ft_putstr_fd(cmds[0], STDOUT_FILENO);
		ft_putstr_fd(": command not found\n", STDOUT_FILENO);
		return (0);
	}
	return (1);
}

static int		pipe_first_command(t_cmd *cmd, t_list **envs)
{
	int i;

	i = 1;
	if (!(basic_first_command(cmd->cmds, envs)))
		return (0);
	while (cmd->cmds[i + 1])
	{
		if (!ft_strcmp(cmd->cmds[i], "|"))
		{
			if (!(basic_first_command(&(cmd->cmds[i + 1]), envs)))
				return (0);
		}
		i++;
	}
	return (1);
}

int				check_first_command(t_cmd *cmd, t_list **envs)
{
	if (cmd->pipe.nb_pipe == 0)
	{
		if (!(basic_first_command(cmd->cmds, envs)))
			return (0);
	}
	else
	{
		if (!(pipe_first_command(cmd, envs)))
			return (0);
	}
	return (1);
}
