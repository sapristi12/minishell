#include "minishell.h"

char			*char_strjoin(char *str, char c)
{
	char	*new;
	int		i;

	if (!(new = malloc(ft_strlen(str) + 2)))
		return (NULL);
	i = 0;
	while (i < ft_strlen(str))
	{
		new[i] = str[i];
		++i;
	}
	new[i++] = c;
	new[i] = 0;
	free(str);
	return (new);
}
