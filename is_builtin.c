#include "minishell.h"

int     is_builtin(char *str)
{
    if (!ft_strcmp(str, "pwd"))
        return (1);
    else if (!ft_strcmp(str, "echo"))
        return (1);
    else if (!ft_strcmp(str, "env"))
        return (1);
    else if (!ft_strcmp(str, "cd"))
        return (1);
    else if (!ft_strcmp(str, "export"))
        return (1);
    else if (!ft_strcmp(str, "unset"))
        return (1);
    else if (!ft_strcmp(str, "exit"))
        return (1);
    return (0);
}
