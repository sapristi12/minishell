#include "minishell.h"

static int 		move_pointer(char 	**cmds)
{
	int i;

	i = 0;
	while (cmds[i] && ft_strcmp(cmds[i], "|"))
		i++;
	return (i + 1);
}

int		init_all_package(t_cmd *cmd, t_list *envs)
{
	int len;
	int pointer;
	int i;

	i = 0;
	pointer = 0;
	len = cmd->pipe.nb_pipe;
	cmd->pipe.all = malloc(sizeof(char **) * (len + 2));
	if (!cmd->pipe.all)
		return (-1);
	cmd->pipe.all[len + 1] = NULL;
	while (i < len + 1)
	{
		cmd->pipe.all[i] = create_package(&(cmd->cmds[pointer]), envs);
		pointer += move_pointer(&(cmd->cmds[pointer]));
		i++;
	}
	return (1);
}

int 	exec_cmd(t_cmd *cmd, t_list *envs, int i)
{
	int ret;

	if (is_builtin(cmd->pipe.all[0][0]))
	{
		printf("BUITIN\n");
		return (1);
	}
	else
	{
		ret = execve(cmd->pipe.all[i][0], cmd->pipe.all[i], NULL);
		if (ret == -1)
		{
			perror("Error:");
			return (0);
		}
	}
	return (1);
}
