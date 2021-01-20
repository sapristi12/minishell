#include "minishell.h"

void    ft_putstr_fd(char *str, int fd)
{
   write(fd, str, ft_strlen(str));
}

void    display_prompt(void)
{
    ft_putstr_fd("minishell $>", 1);
}