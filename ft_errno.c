#include "minishell.h"

static int  errno_parsing_line(int index)
{
    if (index == -1)
        ft_putstr_fd("Error: parsing quotes\n", 1);
    if (index == -2)
        ft_putstr_fd("Error: malloc failed create_space_around\n", 1);
    if (index == -3)
        ft_putstr_fd("Error: parsing line malloc split failed\n", 1);
    if (index == -4)
        ft_putstr_fd("Error: parsing line separators detected\n", 1);
    if (index == -5)
        ft_putstr_fd("Error: parsing line error pipes\n", 1);
    if (index == -6)
        ft_putstr_fd("Error: parsing line error redirections\n", 1);
    if (index == -7)
        ft_putstr_fd("Error: parsing line malloc envs failed\n", 1);
    if (index == -8)
        ft_putstr_fd("Error: command not found\n", 1);
    return (-1);
}

static int  errno_parsing_command(int index)
{
    /*if (index == -1)
        ft_putstr_fd("Error: not command found\n", 1);*/
    return (-1);
}

int     ft_errno(int index)
{
    if (index >= -9 && index <= -1)
        return (errno_parsing_line(index));
    if (index >= -19 && index <= -11)
        return (errno_parsing_command(index % 10));
    return (-1);
}