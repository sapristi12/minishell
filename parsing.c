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

int 	single_command(t_cmd *cmd, t_list **envs)
{
	int ret;

	if (!(parsing_redir(cmd, 0)))
		return (free_error_redir(cmd, envs, 0));
	transform_token(cmd); //sécu si NULL
	ret = exec_cmd(cmd, envs, 0);
	free_package(cmd);
	dup2(cmd->mystdout, STDOUT_FILENO);
	dup2(cmd->mystdin, STDIN_FILENO);
	if (ret == -1)
		return (-2);
	return (1);
}

int 	several_commands(t_cmd *cmd, t_list **envs)
{
	int ret;

	cmd->mystdout = dup(STDOUT_FILENO);
	cmd->mystdin = dup(STDIN_FILENO);
	if (init_pipe(cmd) == -1)
		return (0);
	transform_token(cmd);
	ret = loop_command_pipe(cmd, envs);
	dup2(cmd->mystdout, STDOUT_FILENO);
	dup2(cmd->mystdin, STDIN_FILENO);
	if (ret == -1)
		return (free_end_pipe(cmd, -2));
	pipe_first_command(cmd, envs);
	return (free_end_pipe(cmd, 1));
}

int     parsing_command(t_cmd *cmd, t_list **envs)
{
	if (!(check_first_command(cmd, envs)))
		return (0);
	init_all_package(cmd, envs);
	if (cmd->pipe.nb_pipe == 0)
		return (single_command(cmd, envs));
    else if (cmd->pipe.nb_pipe > 0)
    	return (several_commands(cmd, envs));
}

int     parsing_line(char *prompt, t_list **envs, t_cmd *cmd)
{
    int 	ret;

    init_struct_cmd(cmd);
	if (!(prompt = create_space_around(prompt)))
        return (errno_parsing_line(-2));
    if (!(cmd->cmds = new_split(prompt, ' ')))
        return (errno_parsing_line(-3));
    if (!several_string(cmd->cmds))
        return (errno_parsing_line(free_i(cmd, -4)));
	if (!parsing_pipe(cmd))
        return (errno_parsing_line(free_i(cmd, -5)));
	if (!(parsing_quotes(cmd, envs)))
		return (errno_parsing_line(free_quote(cmd, prompt, -6)));
	if ((ret = parsing_command(cmd, envs)) <= 0)
		return (free_8(prompt, envs, cmd, ret));
	if (cmd->exit_status[0] == 1)
		return (-2);
	free(prompt);
    free_char_double_array(cmd->cmds);
    return (0);
}