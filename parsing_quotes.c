#include "minishell.h"

char 	*get_var_dollar(char *str, t_list **envs)
{
	int		i;
	char	*name;
	char 	*tmp;

	i = 0;
	while (str[i] && str[i] != S_QUOTE && str[i] != D_QUOTE && str[i] != SLASH)
		i++;
	name = malloc(i + 1);
	if (!name)
		return (NULL);
	name[i] = '\0';
	i = 0;
	while (str[i] && str[i] != S_QUOTE && str[i] != D_QUOTE && str[i] != SLASH)
	{
		name[i] = str[i];
		i++;
	}
	tmp = get_env(*envs, name);
	free(name);
	if (tmp)
		return (ft_strdup(tmp));
	return (ft_strdup(""));
}

int 	is_even_quote(char *str)
{
	int		in_quote;
	int 	i;
	char	tmp;

	i = 0;
	in_quote = -1;
	while (str[i])
	{
		if (str[i] == SLASH && (str[i + 1] == SLASH || str[i + 1] == S_QUOTE))
			i++;
		if (in_quote == 1)
		{
			if ((str[i] == tmp && tmp == S_QUOTE) || (((str[i - 1] != SLASH) || (str[i - 1] == SLASH && str[i - 2] == SLASH)) && (tmp == D_QUOTE && str[i] == tmp)))
				in_quote = -in_quote;
		}
		else if (in_quote == -1)
		{
			if (str[i] == S_QUOTE || str[i] == D_QUOTE)
			{
				if (str[i] == S_QUOTE || (i > 0 && (str[i] == D_QUOTE && str[i - 1] != SLASH) || (i == 0 && str[i] == D_QUOTE)))
				{
					tmp = str[i];
					in_quote = -in_quote;
				}
			}
		}
		i++;
	}
	if (in_quote == -1)
		return (1);
	return (0);
}

char 	*manage(char **str, char tmp, t_list **envs)
{
	char 	*copy;

	if (tmp == D_QUOTE)
		copy = double_quote(str[0], envs);
	else
		copy = simple_quote(str[0]);
	return (copy);
}

static int 	move_normal_pointer(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if ((i == 0) || (i > 0 &&  str[i] == SLASH && str[i + 1]))
			i++;
		else if (str[i] == S_QUOTE)
			break;
		else if (str[i] == D_QUOTE && (i > 1 && (str[i - 1] == SLASH && str[i - 2] == SLASH)))
			break;
		else if (str[i] == D_QUOTE && (i > 0 && str[i - 1] != SLASH))
			break;
		i++;
	}
	return (i);
}

static int 	move_pointer(char *str, char tmp)
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

char 	*create_new_str(char *str, t_list **envs)
{
	int		in_quote;
	char	*new;
	char 	*copy;
	char 	tmp;
	char	*save_pointer;

	save_pointer = str;
	in_quote = -1;
	new = malloc(1);
	if (!new)
		return (NULL);
	new[0] = 0;
	while (*str)
	{
		if (in_quote == -1)
		{
			if (*str == S_QUOTE || *str == D_QUOTE)
			{
				tmp = *str;
				in_quote = -in_quote;
				str++;
			}
		}
		if (in_quote == 1 && (*str == tmp))
		{
			in_quote = -in_quote;
			str++;
		}
		else if (in_quote == 1)
		{
			copy = manage(&str, tmp, envs);
			str += move_pointer(str, tmp);
			new = ft_strjoin(new, copy);
			free(copy);
			in_quote = -in_quote;
		}
		else
		{
			copy = normal_quote(str, envs);
			str += move_normal_pointer(str);
			new = ft_strjoin(new, copy);
			free(copy);
		}
	}
	free(save_pointer);
	return (new);
}

int 	parsing_quotes(t_cmd *cmd, t_list **envs)
{
	int		i;

	i = 0;
	while (cmd->cmds[i])
	{
		if (!(is_even_quote(cmd->cmds[i])))
		{
			ft_putstr_fd("ERROR QUOTES PARSING\n", 1);
			return (0);
		}
		if (!(cmd->cmds[i] = create_new_str(cmd->cmds[i], envs)))
		{
			ft_putstr_fd("ERROR IN NEW STRING \n", 1);
			return (0);
		}
		i++;
	}
	i = 0;
	while (cmd->cmds[i + 1])
		i++;
	if (is_token_string(cmd->cmds[i]))
	{
		ft_putstr_fd("ERROR PARSING TOKEN\n", 1);
		return (0);
	}
	return (1);
}