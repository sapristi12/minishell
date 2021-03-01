/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stradd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erlajoua <erlajoua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 15:15:29 by erlajoua          #+#    #+#             */
/*   Updated: 2021/03/01 15:15:30 by erlajoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_stradd(char const *s1, char const *s2)
{
	char	*str1;
	char	*str2;
	char	*dest;
	int		i;
	int		j;

	i = -1;
	j = 0;
	if (!s1 || !s2)
		return (NULL);
	str1 = (char *)s1;
	str2 = (char *)s2;
	if (!(dest = (char *)malloc(ft_strlen(str1) + ft_strlen(str2) + 1)))
		return (NULL);
	while (str1[++i])
		dest[i] = str1[i];
	while (str2[j])
	{
		dest[i + j] = str2[j];
		j++;
	}
	dest[i + j] = '\0';
	return (dest);
}
