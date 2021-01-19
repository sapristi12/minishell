#include "minishell.h"

int     parsing_line(char *cmd, char **envp)
{
    char **cmds;
    int i = 0;

    if (!(cmd = create_space_around(cmd)))
        return (-1);
    if (!(cmds = new_split(cmd, ' ')))
        return (-1);
    printf("->%s\n", cmds[0]);
    if (!ft_strcmp(cmds[0], "exit"))
    {
        printf("gonna quit\n");
        free(cmd);
        int j = 0;
        while (cmds[j])
        {
            free(cmds[j]);
            j++;
        }
        free(cmds);
        printf("return -1 !");
        return (-1);
    }
    (void)cmds;
    (void)envp;
    return (0);
}
