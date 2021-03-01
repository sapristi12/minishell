/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erlajoua <erlajoua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 13:50:31 by erlajoua          #+#    #+#             */
/*   Updated: 2021/03/01 20:54:57 by erlajoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char			*ft_getrest(char *str, int *empty_rest)
{
	char *rest;

	*empty_rest = 0;
	while (*str != '\0')
	{
		if (*str == '\n')
		{
			str++;
			if (!(rest = (char*)malloc(sizeof(char) * ft_strlen(str) + 1)))
				return (NULL);
			rest = ft_strcpy(rest, str);
			return (rest);
		}
		str++;
	}
	*empty_rest = 1;
	return (NULL);
}

static int		ft_manage_rest(t_gnl *s, char **line, char **buffer)
{
	char	*rest;
	char	*subline;
	int		empty_rest;

	empty_rest = 0;
	rest = ft_getrest(*buffer, &empty_rest);
	if (rest == NULL && empty_rest == 0)
		return (-1);
	if (empty_rest == 1)
	{
		if ((*line = ft_strjoin(*line, *buffer)) == NULL)
			return (-1);
		ft_bzero(*buffer, BUFFER_SIZE + 1);
		return (1);
	}
	else
	{
		if ((subline = ft_getline(*buffer)) == NULL)
			return (-1);
		if ((*line = ft_strjoin(*line, subline)) == NULL)
			return (-1);
		s->rest = rest;
		free(subline);
		return (0);
	}
}

static int		ft_rest(t_gnl *s, char **buffer, int fd, char **line)
{
	int ret;

	if (s->rest != NULL)
	{
		*buffer = ft_strcpy(*buffer, s->rest);
		free(s->rest);
		s->rest = NULL;
	}
	else
	{
		s->nb_bytes = read(fd, *buffer, BUFFER_SIZE);
		if (s->nb_bytes == 0 && s->flag == 0)
			return (0);
		else if (s->nb_bytes < 0)
			return (-1);
		else
			s->flag = 1;
	}
	ret = ft_manage_rest(s, line, buffer);
	if (ret == 0)
		return (2);
	if (ret == -1)
		return (-1);
	return (1);
}

static int		ft_read(int fd, t_gnl *s, char **line)
{
	char	*buffer;
	int		ret;

	ret = 0;
	if (!(buffer = malloc(BUFFER_SIZE + 1)))
		return (-1);
	ft_bzero(buffer, BUFFER_SIZE + 1);
	if (!(*line = malloc(1)))
	{
		free(buffer);
		return (-1);
	}
	*line[0] = '\0';
	while (ret != 2)
	{
		ret = ft_rest(s, &buffer, fd, line);
		if (ret <= 0)
		{
			free(buffer);
			return (ret);
		}
	}
	free(buffer);
	return (s->nb_bytes > 0 || s->rest) ? 1 : 0;
}

int				get_next_line(int fd, char **line, int option)
{
	static t_gnl	s;
	int				ret;

	if (option == 1)
		free(s.rest);
	if ((read(fd, 0, 0) < 0 || fd < 0) != 0 || !line)
		return (-1);
	s.flag = 0;
	ret = ft_read(fd, &s, line);
	return (ret);
}
