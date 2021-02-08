#include "minishell.h"

char 	*normal_quote(char *str, t_list **envs)
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
	while (str[i] && ((i > 1 && (str[i - 2] != '\\' && str[i - 1] == '\\')) || str[i] != D_QUOTE))
	{
		if ((str[i] == S_QUOTE && str[i - 1] != '\\') || (str[i] == S_QUOTE && str[i - 1] == '\\' && str[i - 2] != S_QUOTE))
			break ;
		if (i < max && (str[i] == '\\' && str[i + 1] == '\\'))
		{
			new = char_strjoin(new, '\\');
			i += 2;
		}
		else if (i < max && (str[i] == '\\' && str[i + 1] == D_QUOTE))
		{
			new = char_strjoin(new, D_QUOTE);
			i += 2;
		}
		else if (i < max && (str[i] == '\\'))
		{
			new = char_strjoin(new, str[i + 1]);
			i += 2;
		}
		else if (str[i] == '$' && max > 0)
		{
			if ((i > 0 && (str[i - 1] != '\\') || (i > 1 && (str[i - 1] == '\\' && str[i - 2] == '\\')) || i == 0) && (i == max || (i < max && (str[i + 1] != S_QUOTE && str[i + 1] != D_QUOTE))))
			{
				tmp = get_var_dollar(&str[i + 1], envs);
				new = ft_strjoin(new, tmp);
				free(tmp);
				while (str[i] && str[i] != S_QUOTE && str[i] != D_QUOTE)
					i++;
				return (new);
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
	while (str[i] && ((i > 1 && (str[i - 2] != '\\' && str[i - 1] == '\\')) || str[i] != D_QUOTE))
	{
		if (i < max && (str[i] == '\\' && str[i + 1] == '\\'))
		{
			new = char_strjoin(new, '\\');
			i += 2;
		}
		else if (i < max && (str[i] == '\\' && str[i + 1] == D_QUOTE))
		{
			new = char_strjoin(new, D_QUOTE);
			i += 2;
		}
		else if (i < max && (str[i] == '\\' && str[i + 1] == '$'))
		{
			new = char_strjoin(new, str[i + 1]);
			i += 2;
		}
		else if (str[i] == '$' && max > 0)
		{
			if ((i > 0 && (str[i - 1] != '\\') || (i > 1 && (str[i - 1] == '\\' && str[i - 2] == '\\')) || i == 0) && (i == max || (i < max && (str[i + 1] != S_QUOTE && str[i + 1] != D_QUOTE))))
			{
				tmp = get_var_dollar(&str[i + 1], envs);
				new = ft_strjoin(new, tmp);
				free(tmp);
				while (str[i] && str[i] != S_QUOTE && str[i] != D_QUOTE)
					i++;
				return (new);
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
