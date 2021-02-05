#include "minishell.h"

int 	ft_pwd(t_cmd *cmd)
{
	int 	i;
	char	buffer[PATH_MAX];

	i = 0;
	getcwd(buffer, PATH_MAX);
	ft_putstr_fd(buffer, STDOUT_FILENO);
	ft_putstr_fd("\n", STDOUT_FILENO);
	return (1);
}
