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

static void     replace(char **line)
{
    int i;

    i = 0;
    while (*line[i])
    {

        i++;
    }
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
    printf("size : %d\n", size);
    dest = malloc(size + 1);
    if (!dest)
        return (NULL);
    dest[size] = '\0';
    while (str[i])
    {
        if (str[i] == '>' && str[i + 1] == '>')
        {
            dest[j] = ' ';
            dest[j + 1] = '>';
            dest[j + 2] = '>';
            dest[j + 3] = ' ';
            j += 4;
        } else if (str[i] == '|' || str[i] == '<' || (str[i] == '>' && str[i + 1] != '>'))
        {
            dest[j] = ' ';
            dest[j + 1] = '|';
            dest[j + 2] = ' ';
            j += 3;
        } else
        {
            dest[j] = str[i];
            j++;
        }
        i++;
    }
    free(str);
    return (dest);
}
