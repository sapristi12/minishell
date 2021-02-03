#include "minishell.h"

void 	ft_delone(t_list **lst, char *str)
{
	t_list	*envs;
	t_list	*tmp;

	envs = *lst;
	if (!ft_strncmp(envs->content, str, ft_strlen(str)))
	{
		tmp = envs->next;
		free(envs->content);
		free(envs);
		*lst = tmp;
		return ;
	}
	while (envs)
	{
		if (!ft_strncmp(envs->content, str, ft_strlen(str)))
		{
			tmp->next = envs->next;
			free(envs->content);
			free(envs);
			envs = tmp;
		}
		tmp = envs;
		envs = envs->next;
	}
}

int 	ft_unset(t_cmd *cmd, t_list **envs)
{
	int i;

	i = 1;
	while (cmd->cmds[i] && !is_symbol(cmd->cmds[i]))
	{
		printf("going to unset %s\n", cmd->cmds[i]);
		ft_delone(envs, cmd->cmds[i]);
		i++;
	}
}