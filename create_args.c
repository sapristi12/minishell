/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_args.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erlajoua <erlajoua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 18:57:18 by erlajoua          #+#    #+#             */
/*   Updated: 2021/03/05 17:10:52 by erlajoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		is_symbol(char *str)
{
	int		i;
	char	**symbols;

	symbols = (char *[4]){">>", ">", "<", "|"};
	i = 0;
	while (i < 4)
	{
		if (!ft_strcmp(str, symbols[i]))
			return (1);
		i++;
	}
	return (0);
}

char	**free_return(char **dest)
{
	free(dest);
	return (NULL);
}

int		condition(char *s, int j)
{
	if ((!is_symbol(s) || (is_symbol(s) && j == 0)))
		return (1);
	return (0);
}

char	*hub_files(char *cmd, t_list **envs)
{
	struct stat		myst;
	int				ret;
	char			*dest;

	ret = stat(cmd, &myst);
	if (cmd[0] != '/' && ret == -1 && !is_builtin(cmd))
	{
		dest = get_path_command(cmd, envs, 1);
		return (dest);
	}
	else if (cmd[0] == '/' && ret == -1)
		return (NULL);
	return (ft_strdup(cmd));
}

char	**create_package(char **cmds, t_list **envs, int option, int *tab)
{
	char	**dest;
	int		i;

	i = 0;
	while (cmds[i] && ft_strcmp(cmds[i], "|") && condition(cmds[i], tab[i]))
		i++;
	dest = malloc(sizeof(char *) * (i + 1));
	if (!dest)
		return (NULL);
	dest[i] = NULL;
	i = 0;
	while (cmds[i] && ft_strcmp(cmds[i], "|") && condition(cmds[i], tab[i]))
	{
		if (i == 0)
		{
			dest[i] = hub_files(cmds[i], envs);
			if (!(dest[i]) && option != 0)
				return (free_return(dest));
			else if (!(dest[i]))
				dest[i] = ft_strdup("");
		}
		else
			dest[i] = ft_strdup(cmds[i]);
		i++;
	}
	return (dest);
}
