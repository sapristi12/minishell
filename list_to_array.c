#include "minishell.h"

int 	list_length(t_list *envs)
{
	int i;

	i = 0;
	if (!envs)
		return (0);
	while (envs)
	{
		i++;
		envs = envs->next;
	}
	return (i);
}

char 	**list_to_array(t_list *envs)
{
	int		i;
	char 	**dest;

	i = list_length(envs);
	dest = malloc(sizeof(char *) * (i + 1));
	if (!dest)
		return (NULL);
	dest[i] = NULL;
	i = 0;
	while (envs)
	{
		dest[i] = ft_strdup(envs->content);
		envs = envs->next;
		i++;
	}
	return (dest);
}
