/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erlajoua <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 15:11:49 by erlajoua          #+#    #+#             */
/*   Updated: 2021/03/12 10:21:54 by erlajoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	ft_lstadd_back(&(cmd->exported), tmp);
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
