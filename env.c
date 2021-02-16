#include "minishell.h"

void	set_env(t_list **envs, char *env, char *value)
{
	t_list	**begin;
	char	*tmp;
	char 	*new;

	begin = envs;
	tmp = ft_strdup("");
	if (!tmp)
		return ;
	while ((*envs) && ft_strncmp((*envs)->content, env, ft_strlen(env)))
		*envs = (*envs)->next;
	new = ft_strjoin(tmp, env);
	new = char_strjoin(new, '=');
	if (value != NULL)
		new = ft_strjoin(new, value);
	if (*envs == NULL)
	{
		ft_lstadd_back(begin, ft_lstnew(new));
		free(new);
	}
	else
	{
		free((*envs)->content);
		(*envs)->content = new;
	}
}