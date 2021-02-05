#include "minishell.h"

#include "minishell.h"

int		cd_home(t_list **envs)
{
	char	*home;
	int		ret;

	ret = 0;
	if (!(home = ft_strdup(get_env(*envs, "HOME"))))
		return (-1);
	ret = chdir(home);
	if (ret != -1)
	{
		set_env(envs, "OLDPWD", get_env(*envs, "PWD"));
		set_env(envs, "PWD", home);
		free(home);
	}
	return (ret);
}

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

	ret = 0;
	if (!(pwd = ft_strdup(get_env(*envs, "PWD"))))
		return (-1);
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
	ret = chdir("..");
	if (ret != -1)
	{
		getcwd(buffer, PATH_MAX);
		set_env(envs, "OLDPWD", pwd);
		set_env(envs, "PWD", buffer);
	}
	return (ret);
}

int 	ft_cd(t_cmd *cmd, t_list **envs)
{
	int		ret;
	int 	i;

	i = 0;
	ret = 0;
	while (cmd->cmds[i] && !is_symbol(cmd->cmds[i]))
		i++;
	if (i != 2)
		return (0);
	if (!ft_strcmp(cmd->cmds[1], "~"))
		ret = cd_home(envs);
	else if (!ft_strcmp(cmd->cmds[1], "-"))
		ret = cd_old(envs);
	else if (!ft_strcmp(cmd->cmds[1], ".."))
		ret = cd_back(envs);
	else
		ret = cd_basic(cmd->cmds, envs);
	if (ret == -1)
	{
		fprintf(stderr, "error : %s\n", strerror(errno));
		return (1);
	}
}