#include "minishell.h"

char 	*double_quote(char *str, t_list **envs)
{
	char 	*new;
	char 	*tmp;
	int 	i;

	i = 0;
	new = malloc(1);
	if (!new)
		return (NULL);
	new[0] = '\0';
	while (str[i] && (i > 1 && (str[i - 2] != '\\' && str[i - 1] == '\\')) || str[i] != D_QUOTE)
	{
		if (str[i] == '\\' && str[i + 1] == '\\')
		{
			new = char_strjoin(new, '\\');
			i += 2;
		}
		else if (str[i] == '\\' && str[i + 1] == D_QUOTE)
		{
			new = char_strjoin(new, D_QUOTE);
			i += 2;
		}
		else if (str[i] == '$')
		{
			if (str[i - 1] != '\\' && (str[i + 1] != S_QUOTE && str[i + 1] != D_QUOTE))
			{
				tmp = get_var_dollar(&str[i + 1], envs);
				new = ft_strjoin(new, tmp);
				free(tmp);
				while (str[i] && str[i] != S_QUOTE && str[i] != D_QUOTE)
					i++;
			}
			else
			{
				new = char_strjoin(new, '$');
				i += 2;
			}
		}
		else
		{
			new = char_strjoin(new, str[i]);
			i++;
		}
	}
	return (new);
}

char 	*simple_quote(char *str)
{
	char	*new;
	int 	i;

	i = 0;
	while (str[i] && str[i] != S_QUOTE)
		i++;
	new = malloc(i + 1);
	if (!new)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != S_QUOTE)
	{
		new[i] = str[i];
		i++;
	}
	new[i] = '\0';
	return (new);
}
