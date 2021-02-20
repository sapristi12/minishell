#include "minishell.h"

int 		only_spaces(char *str)
{
	int i;

	i = 0;
	while (str[i] && str[i] == ' ')
		i++;
	if (str[i] == '\0')
		return (1);
	return (0);
}
