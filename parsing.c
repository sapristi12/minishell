#include "minishell.h"

int     parsing_line(char *cmd, char **envp)
{
    char **cmds;
    int i = 0;

    cmd = create_space_around(cmd);
    if (!cmd)
        return (-1);
    printf("new cmd : %s\n", cmd);
    /*cmds = new_split(cmd, ' ');
    if (!cmd)
        return (-1);
    while (cmds[i])
    {
        printf(">%s\n", cmds[i]);
        i++;
    }*/
    (void)envp;
}
