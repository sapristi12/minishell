#include "minishell.h"

int     several_string(char **cmds)
{
    int i;
    int j;
    int k;
    char *strs[4];

    strs[0] = ">";
    strs[1] = ">>";
    strs[2] = "<";
    strs[3] = "|";
    i = 0;
    while (cmds[i + 1])
    {
        j = 0;
        while (j < 4)
        {
            if (!ft_strcmp(cmds[i], strs[j]))
            {
                k = 0;
                while (k < 4)
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
