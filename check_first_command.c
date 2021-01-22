#include "minishell.h"

static int      basic_first_command(char **cmds, t_list *envs)
{
	int			ret;
	char		**args;
	pid_t		pid;
	int 		fd_null;

	if (is_builtin(cmds[0]))
		return (1);
	pid = fork();
	if (pid == -1)
	{
		printf("Error forking()\n");
		return (0);
	}
	if (pid == 0)
	{
		fd_null = open("/dev/null", O_RDWR);
		args = create_package(cmds, envs);
		dup2(STDIN_FILENO, fd_null);
		ret = execve(args[0], args, NULL);
		if (ret == -1)
		{
			ft_putstr_fd(args[0], 1);
			ft_putstr_fd(": command not found\n", 1);
			free_char_double_array(args);
			return (0);
		}
	}
	wait(&pid);
	return (1);
}

static int      pipe_first_command(t_cmd *cmd, t_list *envs)
{
    int     i;

    i = 1;
    if (!(basic_first_command(cmd->cmds, envs)))
        return (0);
    while (cmd->cmds[i])
    {
        if (!ft_strcmp(cmd->cmds[i], "|"))
            if (!(basic_first_command(&cmd->cmds[i + 1], envs)))
                return (0);
        i++;
    }
    return (1);
}

int             check_first_command(t_cmd *cmd, t_list *envs)
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