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

int 	loop_command_pipe(t_cmd *cmd, t_list *envs)
{
	int i;

	i = 0;
	if (!(parsing_redir(cmd)))
		return (-1);
	while (cmd->pipe.all[i])
	{
		cmd->pid = fork();
		if (cmd->pid == -1)
			return (-1);
		if (cmd->pid == 0 && i == 0)
			first_fork(cmd, envs, i);
		else if (cmd->pid == 0 && i != cmd->pipe.nb_pipe)
			mid_fork(cmd, envs, i);
		else if (cmd->pid == 0 && i == cmd->pipe.nb_pipe)
			last_fork(cmd, envs, i);
		if (i == 0)
			close(cmd->pipe.fd[0][1]);
		else if (i == cmd->pipe.nb_pipe)
			close(cmd->pipe.fd[cmd->pipe.nb_pipe - 1][0]);
		else
			close_after(cmd, i);
		i++;
	}
	while (cmd->pipe.save-- >= 0)
		wait(&cmd->pid);
	return (1);
}

int     parsing_command(t_cmd *cmd, t_list *envs)
{
	if (!(check_first_command(cmd, envs)))
        return (0);
	init_all_package(cmd, envs);
	if (cmd->pipe.nb_pipe == 0)
	{
		cmd->pid = fork();
		if (cmd->pid == -1)
			perror("Fork:");
		if (cmd->pid == 0)
		{
			if (!(parsing_redir(cmd)))
				return (errno_parsing_line(free_i(cmd, -7)));
			if (!(exec_cmd(cmd, envs, 0)))
				return (0);
		}
		wait(&cmd->pid);
		return (1);
	}
    else if (cmd->pipe.nb_pipe > 0)
	{
		cmd->pipe.fd_saved = dup(STDIN_FILENO);
		if (init_pipe(cmd) == -1)
    		return (0);
    	if (!(loop_command_pipe(cmd, envs)))
    		return (0);
		dup2(cmd->pipe.fd_saved, STDIN_FILENO);
	}
}

int     parsing_line(char *command, char **envp)
{
    t_list  *envs;
    t_cmd   cmd;

    init_struct_cmd(&cmd);
	// if (!(number_quote_is_even(command)))
   //     return (errno_parsing_line(-1));
    if (!(command = create_space_around(command)))
        return (errno_parsing_line(-2));
    if (!(cmd.cmds = new_split(command, ' ')))
        return (errno_parsing_line(-3));
	//show_packages(&cmd);
    if (!several_string(cmd.cmds))
        return (errno_parsing_line(free_i(&cmd, -4)));
	if (!parsing_pipe(&cmd))
        return (errno_parsing_line(free_i(&cmd, -5)));
	if (!(envs = init_list_env(envp)))
        return (errno_parsing_line(free_i(&cmd, -7)));
	if (!(parsing_quotes(&cmd, envs))) //do the return
		return (0);
    if (!(parsing_command(&cmd, envs)))
		return (free_8(command, envs, &cmd));
    ft_lstclear(&envs, free);
    free(command);
    free_char_double_array(cmd.cmds);
    return (0);
}
