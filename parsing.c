#include "minishell.h"

int     parsing_line(char *cmd, char **envp)
{
    char **cmds;
    char *save;
    int i = 0;

    if (!(cmd = create_space_around(cmd)))
        return (-1);
    if (!(cmds = new_split(cmd, ' ')))
        return (-1);
    while (cmds[i])
    {
        printf(">%s\n", cmds[i]);
        i++;
    }
    free(cmd);
    free_char_double_array(cmds);
    return (0);
}
