/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_list_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erlajoua <erlajoua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 20:33:15 by erlajoua          #+#    #+#             */
/*   Updated: 2021/03/12 10:46:42 by erlajoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list		*init_list_env(char **envp)
{
	t_list		*envs;
	t_list		*tmp;
	int			i;

	i = 1;
	if (!(envs = ft_lstnew(envp[0])))
		return (NULL);
	while (envp[i])
	{
		if (!(tmp = ft_lstnew(envp[i])))
		{
			ft_lstclear(&envs, free);
			return (NULL);
		}
		ft_lstadd_back(&envs, tmp);
		i++;
	}
	return (envs);
}
