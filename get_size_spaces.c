/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_size_spaces.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erlajoua <erlajoua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 20:37:46 by erlajoua          #+#    #+#             */
/*   Updated: 2021/03/01 20:37:57 by erlajoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		move_pointer_g(char **str, char c)
{
	int i;

	i = 0;
	while (str[0][i] == c)
		i++;
	while (i-- > 0)
		str[0]++;
	return (1);
}

int				get_size(char *str)
{
	int j;
	int in_quote;

	in_quote = -1;
	j = 0;
	while (*str)
	{
		if (*str == 34)
			in_quote = -in_quote;
		if (*str == SLASH && (*(str + 1) == '|'))
			str++;
		else if (*str == '>' && in_quote == -1)
			j += move_pointer_g(&str, '>');
		else if (*str == '|' && in_quote == -1)
			j += move_pointer_g(&str, '|');
		else if (*str == '<' && in_quote == -1)
			j += move_pointer_g(&str, '<');
		str++;
	}
	return (j * 2);
}
