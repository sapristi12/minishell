
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erlajoua <erlajoua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 13:50:31 by erlajoua          #+#    #+#             */
/*   Updated: 2020/11/25 13:53:56 by erlajoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	dstlen;
	size_t	srclen;
	size_t	i;

	dstlen = 0;
	srclen = 0;
	i = 0;
	while (dst[dstlen])
		dstlen++;
	while (src[srclen])
		srclen++;
	if (dstsize == 0 || dstsize <= dstlen)
		return (srclen + dstsize);
	while (i < srclen && i < dstsize - dstlen - 1)
	{
		dst[dstlen + i] = src[i];
		i++;
	}
	dst[dstlen + i] = '\0';
	return (dstlen + srclen);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	src_len;

	i = 0;
	src_len = 0;
	if (src)
	{
		src_len = ft_strlen(src);
		if (dstsize > 0)
		{
			while (src[i] && (i < (dstsize - 1)))
			{
				dst[i] = src[i];
				i++;
			}
			dst[i] = '\0';
		}
	}
	return (src_len);
}

static int	get_len(char *str)
{
	if (str)
		return (ft_strlen(str));
	else
		return (0);
}

int			fill_line(char **line, char *buffer, int *offset)
{
	int		to_endl;
	char	*new_line;
	int		line_len;

	line_len = get_len(*line);
	to_endl = 0;
	while (buffer[to_endl] && buffer[to_endl] != '\n')
		to_endl++;
	new_line = (char*)calloc(line_len + to_endl + 1, sizeof(char));
	if (!new_line)
		return (-1);
	if (*line != NULL)
	{
		ft_strlcpy(new_line, *line, line_len + 1);
		free(*line);
	}
	ft_strlcat(new_line, buffer, line_len + to_endl + 1);
	*line = new_line;
	if (buffer[to_endl] == '\n')
	{
		*offset += to_endl + 1;
		return (1);
	}
	*offset = 0;
	return (0);
}

#include <string.h>

int			begin_line(char **line, char *buffer, int *offset)
{
	int	to_endl;

	to_endl = 0;
	while (buffer[*offset + to_endl] && buffer[*offset + to_endl] != '\n')
		to_endl++;
	*line = (char*)calloc(to_endl + 1, sizeof(char)); //ft_calloc
	if (!*line)
		return (-1);
	ft_strlcpy(*line, buffer + *offset, to_endl + 1); //ft_strclpy
	if (buffer[*offset + to_endl] == '\n')
	{
		*offset += to_endl + 1;
		return (1);
	}
	*offset = 0;
	return (0);
}

int			get_next_line(int fd, char **line)
{
	static char	buffer[BUFFER_SIZE + 1] = "";
	static int	offset = 0;
	int			end_file;
	int			read_return;
	int			end_line;

	if (fd < 0 || !line || BUFFER_SIZE <= 0)
		return (-1);
	end_file = 0;
	end_line = 0;
	if (offset)
		end_line = begin_line(line, buffer, &offset);
	while (end_line != 1 && !end_file)
	{
		read_return = read(fd, buffer, BUFFER_SIZE);
		if (read_return == -1 || end_line == -1)
			return (-1);
		buffer[read_return] = '\0';
		end_line = fill_line(line, buffer, &offset);
		end_file = read_return < BUFFER_SIZE;
	}
	return (!end_file || offset != 0);
}

