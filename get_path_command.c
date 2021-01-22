#include "minishell.h"

int		ft_dir(char *path, char *exec)
{
	DIR *dir;
	struct dirent *my_dir;

	dir = opendir(path);
	if (!dir)
		return (-1);
	my_dir = readdir(dir);
	while (my_dir != NULL)
	{
		if (!ft_strcmp(my_dir->d_name, exec))
			return (1);
		my_dir = readdir(dir);
	}
	if (closedir(dir) == -1)
		return (-1);
	return (0);
}

char 	*get_path_command(char *command, t_list *envs)
{
	char	**path;
	char	*whole_path;
	char	*tmp;
	int		i;

	i = 0;
	if (!(whole_path = get_env(envs, "PATH")))
		return (NULL);
	if (!(path = new_split(whole_path, ':')))
		return (NULL); //need to free the path
	while (path[i] && !ft_dir(path[i], command))
		i++;
	if (path[i] != NULL && ft_dir(path[i], command) != -1)
	{
		path[i] = ft_stradd(path[i], "/");
		path[i] = ft_stradd(path[i], command);
		tmp = ft_strdup(path[i]);
		free_char_double_array(path);
		return (tmp);
	}
	free_char_double_array(path);
	return (command);
}