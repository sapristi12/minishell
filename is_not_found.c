/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_not_found.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erlajoua <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 12:07:09 by erlajoua          #+#    #+#             */
/*   Updated: 2021/03/12 13:10:50 by erlajoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_slash(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '/')
			return (1);
		i++;
	}
	return (0);
}

int			ft_dir(char *path, char *exec)
{
	DIR				*dir;
	struct dirent	*my_dir;

	dir = opendir(path);
	if (!dir)
		return (0);
	my_dir = readdir(dir);
	while (my_dir != NULL)
	{
		if (!ft_strcmp(my_dir->d_name, exec))
			return ((closedir(dir) * 0) + 1);
		my_dir = readdir(dir);
	}
	closedir(dir);
	return (0);
}

int			get_path_command(char *command, t_list **envs)
{
	char	**path;
	char	*whole_path;
	int		i;

	i = 0;
	if (!(whole_path = get_env(*envs, "PATH")))
		return (0);
	if (!(path = new_split(whole_path, ':')))
		return (0);
	while (path[i] && !ft_dir(path[i], command))
		i++;
	if (path[i] != NULL && ft_dir(path[i], command) != -1)
	{
		free_char_double_array(path);
		return (1);
	}
	free_char_double_array(path);
	return (0);
}

int			is_dir(char *cmd, int option)
{
	DIR		*dir;

	dir = opendir(cmd);
	if (!dir)
		return (0);
	if (option == 1)
	{
		ft_putstr_fd(cmd, STDERR_FILENO);
		ft_putstr_fd(" : is a directory\n", STDERR_FILENO);
	}
	closedir(dir);
	return (1);
}

void		is_not_found(char *cmd, char **envp)
{
	t_list	*envs;

	if (!(envs = init_list_env(envp)))
		return ;
	if (!get_env(envs, "PATH"))
		perror("minishell");
	else if (!ft_strcmp(cmd, ".."))
		hub_join_not_found(cmd);
	else if (is_slash(cmd))
	{
		if (!is_dir(cmd, 1))
			perror("minishell");
	}
	else
	{
		if (!(get_path_command(cmd, &envs)))
			hub_join_not_found(cmd);
	}
	ft_lstclear(&envs, free);
}
