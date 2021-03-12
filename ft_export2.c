/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erlajoua <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 15:11:49 by erlajoua          #+#    #+#             */
/*   Updated: 2021/03/12 11:50:10 by erlajoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env2(t_list **envs, char *str)
{
	t_list	*new_lst;
	t_list	*begin;

	begin = *envs;
	new_lst = *envs;
	if (!str || !ft_strlen(str))
		return (NULL);
	while (new_lst)
	{
		if (!ft_strncmp(new_lst->content, str, ft_strlen(str)))
			return (&new_lst->content[ft_strlen(str) + 1]);
		new_lst = new_lst->next;
	}
	*envs = begin;
	return (NULL);
}

void	exported_list(t_cmd *cmd, int i)
{
	t_list	*tmp;

	if (!(tmp = ft_lstnew(cmd->cmds[i])))
		return ;
	if (cmd->exported == NULL)
	{
		cmd->exported = tmp;
		return ;
	}
	if (!(get_env2(&(cmd->exported), cmd->cmds[i])))
		ft_lstadd_back(&(cmd->exported), tmp);
	else
	{
		free(tmp->content);
		free(tmp);
	}
}

t_list	*copy_list(t_list *envs)
{
	t_list *new;

	new = ft_lstnew(envs->content);
	envs = envs->next;
	while (envs)
	{
		ft_lstadd_back(&new, ft_lstnew((envs->content)));
		envs = envs->next;
	}
	return (new);
}

int		export_list(t_list *envs, t_list *exported)
{
	t_list *new;

	new = copy_list(envs);
	sort_list(new, ft_strcmp);
	ft_affexport(&new);
	if (exported != NULL)
		ft_affexport(&exported);
	ft_lstclear(&new, free);
	return (1);
}
