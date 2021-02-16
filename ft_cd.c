#include "minishell.h"

int		cd_old(t_list **envs)
{
	char	*old = NULL;
	char	buffer[PATH_MAX];
	int		ret;

	ret = 0;
	if (!(old = ft_strdup(get_env(*envs, "OLDPWD"))))
		return (-1);
	getcwd(buffer, PATH_MAX);
	ret = chdir(old);
	if (ret != -1)
	{
		set_env(envs, "PWD", old);
		set_env(envs, "OLDPWD", buffer);
		free(old);
	}
	return (ret);
}

int		cd_basic(char **words, t_list **envs)
{
	int		ret;
	char	*pwd;
	char	buffer[PATH_MAX];

	if (!(get_env(*envs, "PWD")))
		return (-1);
	pwd = ft_strdup(get_env(*envs, "PWD"));
	ret = chdir(words[1]);
	if (ret != -1)
	{
		getcwd(buffer, PATH_MAX);
		set_env(envs, "PWD", buffer);
		set_env(envs, "OLDPWD", pwd);
	}
	free(pwd);
	return (ret);
}

int		cd_back(t_list **envs)
{
	int		ret;
	char	*pwd;
	char	buffer[PATH_MAX];

	pwd = get_env(*envs, "PWD");
	ret = 0;
	if (pwd != NULL)
	{
		ret = chdir("..");
		if (ret != -1)
		{
			getcwd(buffer, PATH_MAX);
			set_env(envs, "OLDPWD", pwd);
			set_env(envs, "PWD", buffer);
		}
	}
	return (ret);
}

int 	ft_cd(t_cmd *cmd, t_list **envs)
{
	int		ret;
	int 	i;

	i = 0;
	while (cmd->cmds[i] && !is_symbol(cmd->cmds[i]))
		i++;
	if (i != 2)
		return (0);
	else if (!ft_strcmp(cmd->cmds[1], "-"))
		ret = cd_old(envs);
	else if (!ft_strcmp(cmd->cmds[1], ".."))
		ret = cd_back(envs);
	else
		ret = cd_basic(cmd->cmds, envs);
	if (ret == -1)
	{
		perror("cd");
		return (1);
	}
	return (1);
}
