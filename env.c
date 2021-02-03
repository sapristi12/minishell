#include "minishell.h"

void	set_env(t_list **envs, char *env, char *value)
{
	t_list	**begin;
	char	*tmp;
	char 	*new;
	t_list 	*used;

	begin = envs;
	used = (t_list *)*envs;
	tmp = malloc(1);
	if (!tmp)
		return ;
	tmp[0] = '\0';
	while (used && ft_strncmp(used->content, env, ft_strlen(env)))
		used = used->next;
	new = ft_strjoin(tmp, env);
	new = char_strjoin(new, '=');
	new = ft_strjoin(new, value);
	if (used == NULL)
		ft_lstadd_back(begin, ft_lstnew(new));
	else
		used->content = new;
}
