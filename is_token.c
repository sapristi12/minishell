#include "minishell.h"

int 	is_token_char(char c)
{
	if (c == '|')
		return (1);
	if (c == SLASH)
		return (1);
	if (c == '>')
		return (1);
	if (c == '<')
		return (1);
	return (0);
}

int		is_token_string(char *str)
{
	if (!(ft_strcmp(str, "|")))
		return (1);
	if (!(ft_strcmp(str, ">>")))
		return (1);
	if (!(ft_strcmp(str, ">")))
		return (1);
	if (!(ft_strcmp(str, "<")))
		return (1);
	return (0);
}