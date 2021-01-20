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
    printf("GONNA FUCKING QUIT\n");
   /* while (av[i])
    {
        printf("will free this\n");
        free(av[i]);
        i++;
    }
    free(av);
    //get_next_line(1, NULL, 0);*/
    return (0);
}
