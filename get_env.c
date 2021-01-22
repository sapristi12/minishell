#include "minishell.h"

char 	*get_env(t_list *envs, char *str)
{
	while (envs)
	{
		if (!ft_strncmp(envs->content, str, ft_strlen(str)))
			return (&envs->content[ft_strlen(str) + 1]);
		envs = envs->next;
	}
	return (NULL);
}