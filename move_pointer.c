#include "minishell.h"

int 	move_pointer(char *str, char tmp)
{
	int i;

	i = 0;
	while (str[i])
	{
		if ((i > 0 && (str[i - 1] != SLASH && str[i] == D_QUOTE)) || (str[i] == D_QUOTE && str[i - 1] == SLASH && str[i - 2] == SLASH))
			break;
		if (str[i] == tmp && tmp == S_QUOTE)
			break;
		i++;
	}
	return (i + 1);
}

int 	move_normal_pointer(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if ((i == 0) || (i > 0 &&  str[i] == SLASH && str[i + 1]))
			i++;
		else if (i > 0 && str[i] == S_QUOTE && str[i - 1] != SLASH)
			break;
		else if (str[i] == D_QUOTE && (i > 1 && (str[i - 1] == SLASH && str[i - 2] == SLASH)))
			break;
		else if (str[i] == D_QUOTE && (i > 0 && str[i - 1] != SLASH))
			break;
		i++;
	}
	return (i);
}
