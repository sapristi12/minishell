/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_pointer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erlajoua <erlajoua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 20:16:47 by erlajoua          #+#    #+#             */
/*   Updated: 2021/03/10 18:51:56 by erlajoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		move_pointer(char *str, char tmp)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (i > 0 && (str[i - 1] != SLASH && str[i] == D_QUOTE))
			break ;
		if (i > 1 && (str[i] == D_QUOTE &&
		str[i - 1] == SLASH && str[i - 2] == SLASH))
			break ;
		if (str[i] == tmp && tmp == S_QUOTE)
			break ;
		i++;
	}
	return (i + 1);
}

int		move_normal_pointer(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == SLASH && str[i + 1])
			i++;
		else if (i > 1 && (str[i] == S_QUOTE && ((str[i - 1] != SLASH)
		|| (str[i - 1] == SLASH && str[i - 2] == SLASH))))
			break ;
		else if (str[i] == D_QUOTE
		&& (i > 1 && (str[i - 1] == SLASH && str[i - 2] == SLASH)))
			break ;
		else if (str[i] == D_QUOTE && (i > 0 && str[i - 1] != SLASH))
			break ;
		else if (str[i] == S_QUOTE)
			break ;
		i++;
	}
	return (i);
}
