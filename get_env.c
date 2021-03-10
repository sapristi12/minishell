/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erlajoua <erlajoua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 19:03:49 by erlajoua          #+#    #+#             */
/*   Updated: 2021/03/10 15:26:32 by erlajoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env(t_list *envs, char *str)
{
	if (!str || !ft_strlen(str))
		return (NULL);
	while (envs)
	{
		if (!ft_strncmp(envs->content, str, ft_strlen(str)) &&
		envs->content[ft_strlen(str)] == '=')
		{
			return (&envs->content[ft_strlen(str) + 1]);
		}
		envs = envs->next;
	}
	return (NULL);
}
