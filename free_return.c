#include "minishell.h"

char 	*free_charchar(char **str)
{
	free(str);
	return (NULL);
}
