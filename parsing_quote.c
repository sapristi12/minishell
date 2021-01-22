#include "minishell.h"

char	*remove_quote(t_cmd *cmd)
{
	cmd = cmd;
	return (NULL);
}

int     number_quote_is_even(char *str)
{
    int i;
    int count;

    i = 0;
    count = 0;
    while (str[i])
    {
        if (str[i] == 34)
            count++;
        i++;
    }
    if (count % 2 == 0)
        return (1);
    return (0);
}
