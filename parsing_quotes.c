#include "minishell.h"

int 	parsing_quotes(t_cmd *cmd, t_list **envs)
{
	int		i;

	i = 0;
	while (cmd->cmds[i])
	{
		if (!(is_even_quote(cmd->cmds[i])))
		{
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
