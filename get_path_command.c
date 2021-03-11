/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path_command.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erlajoua <erlajoua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 19:04:41 by erlajoua          #+#    #+#             */
/*   Updated: 2021/03/10 16:13:49 by erlajoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		t_ft_dir(char *path, char *exec)
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

char	*t_get_path_command(char *command, t_list **envs, int option)
{
	char	**path;
	char	*whole_path;
	char	*tmp;
	char	*tmp2;
	int		i;

	i = 0;
	if (!(whole_path = get_env(*envs, "PATH")))
		return (NULL);
	if (!(path = new_split(whole_path, ':')))
		return (NULL);
	while (path[i] && !t_ft_dir(path[i], command))
		i++;
	if (path[i] != NULL && t_ft_dir(path[i], command) != -1)
	{
		tmp = ft_stradd(path[i], "/");
		tmp2 = ft_stradd(tmp, command);
		free(tmp);
		free_char_double_array(path);
		return (tmp2);
	}
	free_char_double_array(path);
	if (option == 0)
		return (ft_strdup(command));
	return (NULL);
}
