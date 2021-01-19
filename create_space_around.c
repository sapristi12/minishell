#include "minishell.h"

static int get_size(char *str)
{
    int i;
    int j;

    i = 0;
    j = 0;
    while (str[i])
    {
        if (str[i] == '>' && str[i + 1] == '>')
            j++;
        else if (str[i] == '>')
            j++;
        else if (str[i] == '|')
            j++;
        else if (str[i] == '<')
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
    int size;
    int i;
    int j;
    char *dest;

    i = 0;
    j = 0;
    size = get_size(str) + ft_strlen(str);
    dest = malloc(size + 1);
    if (!dest)
        return (NULL);
    dest[size] = '\0';
    while (str[i])
    {
        if (str[i] == '>' && str[i + 1] == '>' && i++)
            j += replace(&dest, j, str[i - 1], 4);
        else if (str[i] == '|' || str[i] == '<' || (str[i] == '>' && str[i + 1] != '>'))
            j += replace(&dest, j, str[i], 3);
        else
            dest[j++] = str[i];
        i++;
    }
    free(str);
    return (dest);
}
