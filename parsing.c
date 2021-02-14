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

char 	*remove_escaped_token(char *str)
{
	int		i;
	char 	*tmp;

	i = 0;
	while (str[i] && !is_token_char(str[i]))
		i++;
	if (!str[i])
		return (ft_strdup(str));
	tmp = malloc(1);
	if (!tmp)
		return (NULL);
	tmp[0] = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == SLASH && is_token_char(str[i + 1]))
		{
			tmp = char_strjoin(tmp, str[i + 1]);
			i++;
		}
		else
			tmp = char_strjoin(tmp, str[i]);
		i++;
	}
	return (tmp);
}

int 	transform_token(t_cmd *cmd)
{
	int		i;
	int 	j;
	char 	*tmp;

	i = 0;
	while (cmd->pipe.all[i])
	{
		j = 0;
		while (cmd->pipe.all[i][j])
		{
			tmp = remove_escaped_token(cmd->pipe.all[i][j]);
			free(cmd->pipe.all[i][j]);
			cmd->pipe.all[i][j] = tmp;
			j++;
		}
		i++;
	}
}

int 	loop_command_pipe(t_cmd *cmd, t_list **envs)
{
	int i;
	int ret;

	i = 0;
	if (!(parsing_redir(cmd)))
		return (-2);
	transform_token(cmd); //sécu si NULL
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
		return (0);
	if ((ret = parsing_command(cmd, envs)) <= 0)
		return (free_8(prompt, envs, cmd, ret));
	if (cmd->exit_status[0] == 1)
		return (-2);
	free(prompt);
    free_char_double_array(cmd->cmds);
    return (0);
}