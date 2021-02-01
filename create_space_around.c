#include "minishell.h"

static int  move_pointer(char **str, char c)
{
    int i;

    i = 0;
    while (str[0][i] == c)
        i++;
    while (i-- > 0)
        str[0]++;
    return (1);
}

static int get_size(char *str)
{
    int j;
    int in_quote;

    in_quote = -1;
    j = 0;
    while (*str)
    {
        if (*str == 34)
            in_quote = -in_quote;
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

static int      get_len(char **str, char c)
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

static int     replace(char **line, int j, char c, int len)
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

char *create_space_around(char *str)
{
    int     size;
    int     j;
    int     in_quote;
    char    *dest;
    char 	tmp;

    j = 0;
    in_quote = -1;
    size = get_size(str) + ft_strlen(str);
    dest = malloc(size + 1);
    if (!dest)
        return (NULL);
    dest[size] = '\0';
    while (*str)
    {
    	if (in_quote == -1 && (*str == D_QUOTE || *str == S_QUOTE))
		{
			tmp = *str;
			in_quote = 1;
		}
        else if (in_quote == 1)
		{
        	if (*str == tmp)
				in_quote = -in_quote;
		}
        if (*str == '>' && in_quote == -1)
            j += replace(&dest, j, '>', get_len(&str, *str));
        else if (*str == '|' || *str == '<' && in_quote == -1)
            j += replace(&dest, j, *str, get_len(&str, *str));
        else
            dest[j++] = *str;
        str++;
    }
    return (dest);
}
