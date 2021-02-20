#include "minishell.h"

char 	*exit_package(char *name)
{
	int		size;
	int		nb;
	char 	*str;

	nb = g_sig;
	size = 0;
	if (nb == 0)
		size = 1;
	while (nb != 0)
	{
		nb /= 10;
		size++;
	}
	str = malloc(size + 1);
	if (!str)
		return (NULL);
	str[size] = 0;
	nb = g_sig;
	while (size-- > 0)
	{
		str[size] = (nb % 10) + 48;
		nb /= 10;
	}
	free(name);
	return (str);
}

char 	*get_var_dollar(char *str, t_list **envs)
{
	int		i;
	char	*name;
	char 	*tmp;

	i = 0;
	while (str[i] && str[i] != S_QUOTE && str[i] != D_QUOTE && str[i] != SLASH && str[i] != '$' && str[i] != ' ' && str[i] != '@' && str[i] != '=' && str[i] != '?')
		i++;
	name = malloc(i + 1);
	if (!name)
		return (NULL);
	name[i] = '\0';
	i = 0;
	while (str[i] && str[i] != S_QUOTE && str[i] != D_QUOTE && str[i] != SLASH && str[i] != '$' && str[i] != ' ' && str[i] != '@' && str[i] != '=' && str[i] != '?')
	{
		name[i] = str[i];
		i++;
	}
	if (i == 0 && str[i] == '?')
		return (exit_package(name));
	tmp = get_env(*envs, name);
	free(name);
	if (tmp)
		return (ft_strdup(tmp));
	return (ft_strdup(""));
}
