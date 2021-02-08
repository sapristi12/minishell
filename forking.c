#include "minishell.h"

int 	mid_fork(t_cmd *cmd, t_list **envs, int i)
{
	char 	**envp;

	dup2(cmd->pipe.fd[i - 1][0], STDIN_FILENO);
	dup2(cmd->pipe.fd[i][1], STDOUT_FILENO);
	close_all(i - 1, cmd->pipe.nb_pipe, cmd->pipe.fd);
	if (is_builtin(cmd->pipe.all[i][0]))
		return (sort_builtin(cmd, envs));
	if (cmd->pipe.all[i][0] != NULL)
	{
		envp = list_to_array(*envs);
		ft_lstclear(envs, free);
		execve(cmd->pipe.all[i][0], cmd->pipe.all[i], envp);
		free_char_double_array(envp);
	}
	return (1);
}

int 	last_fork(t_cmd *cmd, t_list **envs, int i)
{
	char 	**envp;

	dup2(cmd->pipe.fd[cmd->pipe.nb_pipe - 1][0], STDIN_FILENO);
	close_last(i - 1, cmd->pipe.nb_pipe, cmd->pipe.fd);
	if (is_builtin(cmd->pipe.all[i][0]))
		return (sort_builtin(cmd, envs));
	if (cmd->pipe.all[i][0] != NULL)
	{
		envp = list_to_array(*envs);
		ft_lstclear(envs, free);
		execve(cmd->pipe.all[i][0], cmd->pipe.all[i], envp);
		free_char_double_array(envp);
	}
	return (1);
}

int 	first_fork(t_cmd *cmd, t_list **envs, int i)
{
	char 	**envp;

	dup2(cmd->pipe.fd[0][1], STDOUT_FILENO);
	close_first(i + 1, cmd->pipe.nb_pipe, cmd->pipe.fd);
	if (is_builtin(cmd->pipe.all[i][0]))
		return (sort_builtin(cmd, envs));
	if (cmd->pipe.all[i][0] != NULL)
	{
		envp = list_to_array(*envs);
		ft_lstclear(envs, free);
		execve(cmd->pipe.all[i][0], cmd->pipe.all[i], envp);
		free_char_double_array(envp);
	}
	return (1);
}
