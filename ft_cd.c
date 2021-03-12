/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erlajoua <erlajoua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 17:47:12 by erlajoua          #+#    #+#             */
/*   Updated: 2021/03/12 12:52:23 by erlajoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		cd_old(t_list **envs)
{
	char	*old;
	char	buffer[PATH_MAX];
	int		ret;

	old = NULL;
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

int		cd_home(t_list **envs)
{
	char	**words;
	int		ret;

	if (!get_env(*envs, "HOME"))
		return (-2);
	words = malloc(sizeof(char *) * 2);
	if (!(words))
		return (-1);
	words[0] = deux_strdup("cd");
	words[1] = deux_strdup("~");
	words[1] = create_new_str(words[1], envs);
	ret = cd_basic(words, envs);
	free(words[0]);
	free(words[1]);
	free(words);
	return (ret);
}

int		ft_cd(t_cmd *cmd, t_list **envs)
{
	int		ret;
	int		i;

	i = 0;
	while (cmd->cmds[i] && !is_symbol(cmd->cmds[i]))
		i++;
	if ((i > 2 || (i == 2)) && (is_space(cmd->cmds[1]) || i > 2))
	{
		ft_putstr_fd("minishell: cd: too many arguments\n", STDERR_FILENO);
		return (-1);
	}
	if (i == 1 || !ft_strcmp(cmd->cmds[1], ""))
		ret = cd_home(envs);
	else if (!ft_strcmp(cmd->cmds[1], "-"))
		ret = cd_old(envs);
	else if (!ft_strcmp(cmd->cmds[1], ".."))
		ret = cd_back(envs);
	else
		ret = cd_basic(cmd->cmds, envs);
	if (ret == -1)
		perror("cd");
	if (ret == -2)
		ft_putstr_fd("minishell: cd: HOME not set\n", STDERR_FILENO);
	return (1);
}
