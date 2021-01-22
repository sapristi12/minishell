#include "minishell.h"

void    free_char_double_array(char **av)
{
    int i;

    i = 0;
    while (av[i])
    {
        free(av[i]);
        i++;
    }
    free(av);
}

int    free_parsing_line(char **av, char *line)
{
    int i;

    i = 0;
    ft_putstr_fd("Main loop free\n", 1);
    return (1);
}
