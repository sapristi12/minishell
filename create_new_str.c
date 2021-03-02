/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_new_str.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erlajoua <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 10:34:29 by erlajoua          #+#    #+#             */
/*   Updated: 2021/03/02 10:42:55 by erlajoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			quote_manage(char **str, char **new, t_quo *q, t_list **envs)
{
	char	*copy;

	if (q->tmp == D_QUOTE)
		copy = double_quote(str[0], envs);
	else
		copy = simple_quote(str[0]);
	(*str) += move_pointer(*str, q->tmp);
	*new = ft_strjoin(*new, copy);
	q->in_quote = -(q->in_quote);
	free(copy);
}

void			normal_manage(char **str, char **new, t_list **envs)
{
	char	*copy;

	copy = normal_quote(*str, envs);
	str[0] += move_normal_pointer(*str);
	*new = ft_strjoin(*new, copy);
	free(copy);
}

static void		first_condition(char **str, t_quo *q, char c)
{
	q->tmp = c;
	q->in_quote = -(q->in_quote);
	str[0]++;
}

static void		second_condition(char **str, t_quo *q)
{
	q->in_quote = -(q->in_quote);
	str[0]++;
}

char			*create_new_str(char *str, t_list **envs)
{
	t_quo	q;
	char	*new;
	char	*save_pointer;

	save_pointer = str;
	q.in_quote = -1;
	new = ft_strdup("");
	if (!new)
		return (NULL);
	while (*str)
	{
		if (q.in_quote == -1)
			if (*str == S_QUOTE || *str == D_QUOTE)
				first_condition(&str, &q, *str);
		if (q.in_quote == 1 && (*str == q.tmp))
			second_condition(&str, &q);
		else if (q.in_quote == 1)
			quote_manage(&str, &new, &q, envs);
		else
			normal_manage(&str, &new, envs);
	}
	free(save_pointer);
	return (new);
}
