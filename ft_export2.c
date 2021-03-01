/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erlajoua <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 15:11:49 by erlajoua          #+#    #+#             */
/*   Updated: 2021/03/01 15:14:44 by erlajoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int		export_list(t_list *envs)
{
	t_list *new;

	new = copy_list(envs);
	sort_list(new, ft_strcmp);
	ft_affexport(&new);
	ft_lstclear(&new, free);
	return (1);
}
