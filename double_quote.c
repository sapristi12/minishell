#include "minishell.h"

static int		is_escaped(char c)
{
	if (c == '$')
		return (1);
	if (c == SLASH)
		return (1);
	if (c == D_QUOTE)
		return (1);
	return (0);
}

char 	*double_quote(char *str, t_list **envs)
{
	char 	*new;
	char 	*tmp;
	int 	i;
	int 	max;

	max = ft_strlen(str) - 1;
	i = 0;
	new = malloc(1);
	if (!new)
		return (NULL);
	new[0] = '\0';
	while (str[i] && str[i] != D_QUOTE)
	{
		if (i < max && str[i] == SLASH && is_escaped(str[i + 1]))
		{
			new = char_strjoin(new, str[i + 1]);
			i += 2;
		}
		else if (str[i] == '$' && max > 0)
		{
			tmp = get_var_dollar(&str[i + 1], envs);
			new = ft_strjoin(new, tmp);
			free(tmp);
			while (str[i] && str[i] != S_QUOTE && str[i] != D_QUOTE)
				i++;
			return (new);
		}
		else
		{
			new = char_strjoin(new, str[i]);
			i++;
		}
	}
	return (new);
}
