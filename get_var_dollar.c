#include "minishell.h"

char 	*get_var_dollar(char *str, t_list **envs)
{
	int		i;
	char	*name;
	char 	*tmp;

	i = 0;
	while (str[i] && str[i] != S_QUOTE && str[i] != D_QUOTE && str[i] != SLASH && str[i] != '$' && str[i] != ' ')
		i++;
	name = malloc(i + 1);
	if (!name)
		return (NULL);
	name[i] = '\0';
	i = 0;
	while (str[i] && str[i] != S_QUOTE && str[i] != D_QUOTE && str[i] != SLASH && str[i] != '$' && str[i] != ' ')
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
