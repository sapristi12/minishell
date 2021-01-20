#include "minishell.h"

static int get_size(char *str)
{
    int i;
    int j;
    int in_quote;

    in_quote = -1;
    i = 0;
    j = 0;
    while (str[i])
    {
        if (str[i] == 34)
            in_quote = -in_quote;
        else if (str[i] == '>' && in_quote == -1)
        {
            j++;
            while (str[i] == '>')
                i++;
        }
        else if (str[i] == '|' && in_quote == -1)
        {
            j++;
            while (str[i] == '|')
                i++;
        }
        else if (str[i] == '<' && in_quote == -1)
        {
            j++;
            while (str[i] == '<')
                i++;
        }
        i++;
    }
    return (j * 2);
}

static int      get_len(char **str, char c, int i)
{
    int len;
    int save;

    len = 0;
    if (c == '>')
    {
        len = 0;
        while (str[0][len] && str[0][len] == '>')
            len++;
        len += 2;
    }
    else
    {
        len = 3;
    }
    save = len - i - 3; //maybe - 2
    if (c == '>')
    {
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
        {
            line[0][j + i] = ' ';
        }
        else
        {
            line[0][j + i] = c;
        }
        i++;
    }
    return (len);
}

char *create_space_around(char *str)
{
    int     size;
    int     i;
    int     j;
    int     in_quote;
    char    *dest;

    i = 0;
    j = 0;
    in_quote = -1;
    size = get_size(str) + ft_strlen(str);
    dest = malloc(size + 1);
    if (!dest)
        return (NULL);
    dest[size] = '\0';
    while (*str)
    {
        if (*str == 34)
            in_quote = -in_quote;
        if (*str == '>' && in_quote == -1)
            j += replace(&dest, j, '>', get_len(&str, *str, i));
        else if (*str == '|' || *str == '<' && in_quote == -1)
            j += replace(&dest, j, *str, get_len(&str, *str, i));
        else
            dest[j++] = *str;
        str++;
    }
    return (dest);
}
