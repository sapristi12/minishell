#include "minishell.h"

int     several_string(char **cmds, char *str)
{
    int i;

    i = 0;
    while (cmds[i + 1])
    {
        if (!ft_strcmp(cmds[i], str) && !ft_strcmp(cmds[i + 1], str))
            return (0);
        i++;
    }
    return (1);
}
