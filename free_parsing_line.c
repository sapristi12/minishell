#include "minishell.h"

int 	free_8(char *str, t_list *envs, t_cmd *cmd)
{
	free(str);
	ft_lstclear(&envs, free);
	free_char_double_array(cmd->cmds);
	return (-1);
}

void    free_char_double_array(char **strs)
{
	int i;

	i = 0;
	while (strs[i])
	{
		free(strs[i]);
		i++;
	}
	free(strs);
}

int 	free_i(t_cmd *cmd, int index)
{
	printf("go free\n");
	free_char_double_array(cmd->cmds);
	return (index);
}

int    free_parsing_line(char **av, char *line, int status)
{
    int i;

    i = 0;
    if (status == -2)
    	free_char_double_array(av);
    return (1);
}
