/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erlajoua <erlajoua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 13:54:13 by erlajoua          #+#    #+#             */
/*   Updated: 2021/03/01 20:54:09 by erlajoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strcpy(char *dest, char *src)
{
	int i;

	i = 0;
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = src[i];
	return (dest);
}

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*ptr;

	ptr = (unsigned char*)s;
	while (n > 0)
	{
		*(ptr++) = 0;
		n--;
	}
}

int		ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_getline(char *str)
{
	int		length;
	int		i;
	char	*line;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	length = i;
	if (!(line = (char*)malloc(sizeof(char) * (length + 1))))
		return (NULL);
	i = 0;
	while (i < length)
	{
		line[i] = str[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str1;
	char	*str2;
	char	*dest;
	int		i;
	int		j;

	if (!s1 || !s2)
		return (NULL);
	str1 = (char*)s1;
	str2 = (char*)s2;
	i = -1;
	j = -1;
	if (!(dest = malloc(sizeof(char*) *
	(ft_strlen(str1) + ft_strlen(str2) + 1))))
		return (NULL);
	while (str1[++i])
		dest[i] = str1[i];
	while (str2[++j])
		dest[i + j] = str2[j];
	dest[i + j] = '\0';
	free(str1);
	return (dest);
}
