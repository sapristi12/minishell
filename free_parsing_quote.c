#include "minishell.h"


int			free_quote(t_cmd *cmd, char *prompt, int index)
{
	free_char_double_array(cmd->cmds);
	free(prompt);
	return (index);
}
