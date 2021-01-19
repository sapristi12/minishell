/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erlajoua <erlajoua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 12:00:09 by erlajoua          #+#    #+#             */
/*   Updated: 2020/11/17 12:00:13 by erlajoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strcpyt(char *str, char c)
{
	char	*dest;
	int		i;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	dest = (char *)malloc(sizeof(char) * i + 1);
	if (!dest)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != c)
	{
		dest[i] = str[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

int		cw(char *str, char c)
{
	int i;

	i = 0;
	while (*str)
	{
		while (*str && *str == c)
			str++;
		if (*str && *str != c)
		{
			i++;
			while (*str && *str != c)
				str++;
		}
	}
	return (i);
}

char	**ft_split(char const *s, char c, int *len)
{
	char	*str;
	char	**dest;
	int		i;

	*len = 0;
	if (!s)
		return (NULL);
	str = (char *)s;
	i = 0;
	if (!(dest = (char **)malloc(sizeof(char *) * (cw(str, c) + 1))))
		return (NULL);
	while (*str)
	{
		while (*str && *str == c)
			str++;
		if (*str && *str != c)
		{
			dest[i] = ft_strcpyt(str, c);
			i++;
			while (*str && *str != c)
				str++;
		}
	}
	*len = i;
	dest[i] = NULL;
	return (dest);
}
