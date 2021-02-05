#include "minishell.h"

void    show_packages(t_cmd *cmd)
{
    int i;

    i = 0;
    while (cmd->cmds[i])
    {
        printf("[%s]\n", cmd->cmds[i]);
        i++;
    }
}

int 	loop_command_pipe(t_cmd *cmd, t_list **envs)
{
	int i;
	int ret;

	i = 0;
	if (!(parsing_redir(cmd)))
		return (-1);
	while (i < cmd->pipe.nb_pipe + 1)
	{
		ret = 0;
		cmd->pid = fork();
		if (cmd->pid == -1)
			return (-1);
		if (cmd->pid == 0 && i == 0)
			ret = first_fork(cmd, envs, i);
		else if (cmd->pid == 0 && i != cmd->pipe.nb_pipe)
			ret = mid_fork(cmd, envs, i);
		else if (cmd->pid == 0 && i == cmd->pipe.nb_pipe)
			ret = last_fork(cmd, envs, i);
		if (i == 0)
			close(cmd->pipe.fd[0][1]);
		else if (i == cmd->pipe.nb_pipe)
			close(cmd->pipe.fd[cmd->pipe.nb_pipe - 1][0]);
		else
			close_after(cmd, i);
		if (ret == 1)
			return (-1);
		i++;
	}
	while (cmd->pipe.save-- >= 0)
		wait(&(cmd->pid));
	return (1);
}

int     parsing_command(t_cmd *cmd, t_list **envs)
{
	int ret;

	ret = 0;
	if (!(check_first_command(cmd, envs)))
		return (0);
	init_all_package(cmd, envs);
	if (cmd->pipe.nb_pipe == 0)
	{
		if (!(parsing_redir(cmd)))
			return (errno_parsing_line(free_i(cmd, -7)));
		ret = exec_cmd(cmd, envs, 0);
		free_package(cmd);
		dup2(cmd->mystdout, STDOUT_FILENO);
		dup2(cmd->mystdin, STDIN_FILENO);
		if (ret == -1)
			return (-2);
		return (1);
	}
    else if (cmd->pipe.nb_pipe > 0)
	{
		cmd->mystdout = dup(STDOUT_FILENO);
		cmd->mystdin = dup(STDIN_FILENO);
		if (init_pipe(cmd) == -1)
    		return (0);
    	ret = loop_command_pipe(cmd, envs);
		dup2(cmd->mystdout, STDOUT_FILENO);
		dup2(cmd->mystdin, STDIN_FILENO);
		if (ret == -1)
			return (free_end_pipe(cmd, -2));
		pipe_first_command(cmd, envs);
		return (free_end_pipe(cmd, 1));
	}
}

int     parsing_line(char *command, t_list **envs)
{
    t_cmd   cmd;
	int 	ret;

	ret = 0;
    init_struct_cmd(&cmd);
	if (!(command = create_space_around(command)))
        return (errno_parsing_line(-2));
    if (!(cmd.cmds = new_split(command, ' ')))
        return (errno_parsing_line(-3));
    if (!several_string(cmd.cmds))
        return (errno_parsing_line(free_i(&cmd, -4)));
	if (!parsing_pipe(&cmd))
        return (errno_parsing_line(free_i(&cmd, -5)));
	if (!(parsing_quotes(&cmd, envs))) //do the return
		return (0);
	if ((ret = parsing_command(&cmd, envs)) <= 0)
		return (free_8(command, envs, &cmd, ret));
	free(command);
    free_char_double_array(cmd.cmds);
    return (0);
}
