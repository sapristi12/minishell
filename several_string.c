#include "minishell.h"

int     several_string(char **cmds)
{
    int i;
    int j;
    int k;
    char *strs[3];

    strs[0] = ">";
    strs[1] = ">>";
    strs[2] = "<";
    i = 0;
    while (cmds[i + 1])
    {
        j = 0;
        while (j < 3)
        {
            if (!ft_strcmp(cmds[i], strs[j]))
            {
                k = 0;
                while (k < 3)
                {
                    if (!ft_strcmp(cmds[i + 1], strs[k]))
                        return (0);
                    k++;
                }
            }
            j++;
        }
        i++;
    }
    return (1);
}
