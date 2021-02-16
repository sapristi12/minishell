#include "minishell.h"

int     several_string(char **cmds)
{
    int i;
    int j;
    int k;
    char **strs;

    strs = (char *[5]){">", ">>", "<", "|", NULL};
    i = 0;
    while (cmds[i + 1])
    {
        j = -1;
        while (++j < 4)
        {
            if (!ft_strcmp(cmds[i], strs[j]))
            {
                k = -1;
                while (++k < 4)
                {
                    if (!ft_strcmp(cmds[i + 1], strs[k]))
                        return (0);
                }
            }
        }
        i++;
    }
    return (1);
}
