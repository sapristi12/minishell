#include "minishell.h"

char	*ft_strcpyt(char *str, char c, int in_quote)
{
    char	*dest;
    int		i;
    int     size;

    i = 0;
    size = 0;
    while (str[i] && (str[i] != c || in_quote == 1))
    {
        i++;
        if (str[i] == 34)
            in_quote = -in_quote;
    }
    size = i;
    dest = (char *)malloc(sizeof(char) * (size + 1));
    if (!dest)
        return (NULL);
    i = 0;
    while (i < size)
    {
        dest[i] = str[i];
        i++;
    }
    dest[i] = '\0';
    return (dest);
}

int		cw(char *str, char c)
{
    int i;
    int in_quote;

    in_quote = -1;
    i = 0;
    while (*str)
    {
        while (*str && (*str == c && in_quote == -1))
        {
            if (*str == 34)
                in_quote = -in_quote;
            str++;
        }
        if (in_quote == -1)
        {
            while (*str && (*str != 34 && in_quote == 1))
                str++;
            if (*str == 34)
                in_quote = -in_quote;
        }
        if (*str && (*str != c || in_quote == 1))
        {
            i++;
            while (*str && (*str != c || in_quote == 1))
            {
                str++;
                if (*str == 34)
                    in_quote = -in_quote;
            }
        }
    }
    return (i);
}

char    **new_split(char *str, char c)
{
    char	**dest;
    int		i;
    int     in_quote;

    in_quote = -1;
    i = 0;
    int countword = cw(str, c);
    printf("j'ai alloc %d mots odnt le null\n", countword + 1);
    if (!(dest = (char **)malloc(sizeof(char *) * (countword + 1))))
        return (NULL);
    while (*str)
    {
        while (*str && (*str == c && in_quote == -1))
        {
            if (*str == 34)
                in_quote = -in_quote;
            str++;
        }
        if (in_quote == -1)
        {
            while (*str && (*str != 34 && in_quote == 1))
                str++;
            if (*str == 34)
                in_quote = -in_quote;
        }
        if (*str && *str != c)
        {
            dest[i] = ft_strcpyt(str, c, in_quote);
            i++;
            while (*str && (*str != c || in_quote == 1)) {
                str++;
                if (*str == 34)
                    in_quote = -in_quote;
            }
        }
    }
    dest[i] = NULL;
    return (dest);
}
