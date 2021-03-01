/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erlajoua <erlajoua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 15:15:12 by erlajoua          #+#    #+#             */
/*   Updated: 2021/03/01 15:15:13 by erlajoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char			*char_strjoin(char *str, char c)
{
	char	*new;
	int		i;

	if (!(new = malloc(ft_strlen(str) + 2)))
		return (NULL);
	i = 0;
	while (i < ft_strlen(str))
	{
		new[i] = str[i];
		++i;
	}
	new[i++] = c;
	new[i] = 0;
	free(str);
	return (new);
}
