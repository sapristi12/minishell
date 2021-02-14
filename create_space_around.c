#include "minishell.h"

static int		move_pointer(char **str, char c)
{
	int i;

	i = 0;
	while (str[0][i] == c)
		i++;
	while (i-- > 0)
		str[0]++;
	return (1);
}

int		get_size(char *str)
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
			j += move_pointer(&str, '>');
		else if (*str == '|' && in_quote == -1)
			j += move_pointer(&str, '|');
		else if (*str == '<' && in_quote == -1)
			j += move_pointer(&str, '<');
		str++;
	}
	return (j * 2);
}

static int		get_len(char **str, char c)
{
	int len;
	int save;

	len = 3;
	if (c == '>')
	{
		len = 0;
		while (str[0][len] && str[0][len] == '>' && len < 2)
			len++;
		len += 2;
		save = len - 3;
		while (save-- > 0)
			str[0]++;
	}
	return (len);
}

static int		replace(char **line, int j, char c, int len)
{
	int i;

	i = 0;
	while (i < len)
	{
		if (i == 0 || i == len - 1)
			line[0][j + i] = ' ';
		else
			line[0][j + i] = c;
		i++;
	}
	return (len);
}

int 			escape_token(char **line, int j, char c, char **str)
{
	line[0][j] = SLASH;
	line[0][j + 1] = c;
	str[0]++;
	str[0]++;
	return (2);
}

char			*create_space_around(char *str)
{
	t_space s;

	if (!(init_space(&s, str)))
		return (NULL);
	while (*str)
	{
		if (*str == SLASH && (is_token_char(*(str + 1))))
			s.j += escape_token(&(s.dest), s.j, *(str + 1), &str);
		else
		{
			if (s.in_quote == -1 && (*str == D_QUOTE || *str == S_QUOTE))
			{
				s.tmp = *str;
				s.in_quote = 1;
			} else if (s.in_quote == 1)
			{
				if (*str == s.tmp)
					s.in_quote = -(s.in_quote);
			}
			if ((*str == '>') && s.in_quote == -1)
				s.j += replace(&(s.dest), s.j, '>', get_len(&str, *str));
			else if ((*str == '|' || *str == '<') && s.in_quote == -1)
				s.j += replace(&(s.dest), s.j, *str, get_len(&str, *str));
			else
				s.dest[s.j++] = *str;
			str++;
		}
	}
	return (s.dest);
}
