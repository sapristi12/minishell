#include "minishell.h"

char 	*get_tilde_path(char *str, t_list **envs)
{
	int		i;
	char 	*dest;

	i = 0;
	dest = ft_strdup(get_env(*envs, "HOME"));
	if (!dest)
		return (NULL);
	while (*str && *str != '~')
		str++;
	str++;
	while (str[i])
	{
		dest = char_strjoin(dest, str[i]);
		i++;
	}
	return (dest);
}