/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erlajoua <erlajoua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 18:59:48 by erlajoua          #+#    #+#             */
/*   Updated: 2021/03/01 19:00:20 by erlajoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_env(t_list **envs, char *env, char *value)
{
	t_list		**begin;
	char		*tmp;
	char		*new;
	t_list		*used;

	begin = envs;
	used = (t_list *)*envs;
	tmp = ft_strdup("");
	if (!tmp)
		return ;
	while (used && ft_strncmp(used->content, env, ft_strlen(env)))
		used = used->next;
	new = ft_strjoin(tmp, env);
	new = char_strjoin(new, '=');
	new = ft_strjoin(new, value);
	if (used == NULL)
	{
		ft_lstadd_back(begin, ft_lstnew(new));
		free(new);
	}
	else
	{
		free(used->content);
		used->content = new;
	}
}
