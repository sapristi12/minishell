/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erlajoua <erlajoua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 15:15:05 by erlajoua          #+#    #+#             */
/*   Updated: 2021/03/03 10:04:14 by erlajoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			ft_affexport(t_list **lst)
{
	t_list *tmp;

	tmp = *lst;
	while (tmp != NULL)
	{
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		ft_putstr_fd(tmp->content, STDOUT_FILENO);
		ft_putstr_fd("\n", STDOUT_FILENO);
		tmp = tmp->next;
	}
}

void			ft_afflist(t_list **lst)
{
	t_list *tmp;

	tmp = *lst;
	while (tmp != NULL)
	{
		ft_putstr_fd(tmp->content, 1);
		ft_putstr_fd("\n", 1);
		tmp = tmp->next;
	}
}

void			ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*tmp;

	tmp = *lst;
	while (*lst != NULL)
	{
		tmp = (*lst)->next;
		del((*lst)->content);
		free(*lst);
		*lst = tmp;
	}
	*lst = NULL;
}

void			ft_lstadd_back(t_list **alst, t_list *new)
{
	t_list	*begin;

	if (new)
	{
		if (!(*alst))
			*alst = new;
		else
		{
			begin = *alst;
			while (begin->next)
				begin = begin->next;
			begin->next = new;
		}
	}
}

t_list			*ft_lstnew(void *content)
{
	t_list *list;

	list = malloc(sizeof(t_list));
	if (!list)
		return (NULL);
	list->content = ft_strdup((char *)content);
	if (!list->content)
		return (NULL);
	list->next = NULL;
	return (list);
}
