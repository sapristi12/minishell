#include "minishell.h"

int 	is_alpha(char c)
{
	if (c >= 'a' && c <= 'z')
		return (1);
	if (c >= 'A' && c <= 'Z')
		return (1);
}

int 	is_alnum(char c)
{
	if (is_alpha(c))
		return (1);
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int 	is_valid_before(char *str)
{
	int i;

	i = 0;
	while (str[i] && str[i] != '=')
	{
		if (i == 0 && is_alpha(str[i]))
			i++;
		else if (is_alnum(str[i]))
			i++;
		else
			return (0);
	}
	return (1);
}

char 	*create_env(char *str)
{
	int		i;
	char 	*before;

	i = 0;
	before = ft_strdup("");
	while (str[i] && str[i] != '=')
	{
		before = char_strjoin(before, str[i]);
		i++;
	}
	if (!(is_valid_before(before)))
	{
		free(before);
		return (NULL);
	}
	if (str[i] == '=')
		i++;
	before = char_strjoin(before, '=');
	while (str[i])
	{
		before = char_strjoin(before, str[i]);
		i++;
	}
	return (before);
}