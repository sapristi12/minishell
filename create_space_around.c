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
        if (str[i] == '>' && str[i + 1] == '>' && in_quote == -1)
            j++;
        else if (str[i] == '>' && in_quote == -1)
            j++;
        else if (str[i] == '|' && in_quote == -1)
            j++;
        else if (str[i] == '<' && in_quote == -1)
            j++;
        i++;
    }
    return (j * 2);
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
    while (str[i])
    {
        if (str[i] == 34)
            in_quote = -in_quote;
        if (str[i] == '>' && str[i + 1] == '>' && in_quote == -1 && i++)
            j += replace(&dest, j, str[i - 1], 4);
        else if ((str[i] == '|' || str[i] == '<' || (str[i] == '>' && str[i + 1] != '>')) && in_quote == -1)
            j += replace(&dest, j, str[i], 3);
        else
            dest[j++] = str[i];
        i++;
    }
    return (dest);
}
