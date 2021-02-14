#include "minishell.h"

t_list	*copy_list(t_list *envs)
{
	t_list *new;

	new = ft_lstnew(envs->content);
	envs = envs->next;
	while (envs)
	{
		ft_lstadd_back(&new, ft_lstnew((envs->content)));
		envs = envs->next;
	}
	return (new);
}

int 	export_list(t_list *envs)
{
	t_list *new;

	new = copy_list(envs);
	sort_list(new, ft_strcmp);
	ft_affexport(&new);
	ft_lstclear(&new, free);
	return (1);
}

void 	error_identifier(char *str)
{
	ft_putstr_fd("minishell: export: ", 1);
	ft_putstr_fd(str, 1);
	ft_putstr_fd(": not a valid identifier\n", 1);
}

int 	ft_export(t_cmd *cmd, t_list *envs)
{
	char 	*tmp;
	int		i;

	i = 0;
	while (cmd->cmds[i] && !is_symbol(cmd->cmds[i]))
		i++;
	if (i == 1)
		return (export_list(envs));
	i = 1;
	while (cmd->cmds[i] && !is_symbol(cmd->cmds[i]))
	{
		if (is_there_char(cmd->cmds[i], '='))
		{
			if (!(tmp = create_env(cmd->cmds[i])))
				error_identifier(cmd->cmds[i]);
			else
			{
				ft_lstadd_back(&envs, ft_lstnew(tmp));
				free(tmp);
			}
		}
		i++;
	}
	return (1);
}
