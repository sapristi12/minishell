#include "minishell.h"

int 		only_zeros(char *str)
{
	int i;

	i = 0;
	while (str[i] && str[i] == '0')
		i++;
	if (str[i] == '\0')
		return (1);
	return (0);
}

static int 	third_case(t_cmd *cmd)
{
	cmd->exit_status[0] = 0;
	ft_putstr_fd("minishell: exit: too many arguments\n", 1);
	cmd->exit_status[1] = 1;
	return (1);
}

static int 	second_case(t_cmd *cmd)
{
	if (only_zeros(cmd->cmds[1]))
	{
		cmd->exit_status[1] = 0;
		return (1);
	}
	ft_putstr_fd("minishell: exit: ", 1);
	ft_putstr_fd(cmd->cmds[1], 1);
	ft_putstr_fd(": numeric argument required\n", 1);
	ft_putstr_fd("exit\n", 1);
	cmd->exit_status[1] = 2;
	return (1);
}

static int 	first_case(t_cmd *cmd)
{
	cmd->exit_status[1] = 0;
	ft_putstr_fd("exit\n", 1);
	return (1);
}

static int	fourth_case(t_cmd *cmd)
{
	ft_putstr_fd("minishell: exit: ", 1);
	ft_putstr_fd(cmd->cmds[1], 1);
	ft_putstr_fd(": numeric argument required\n", 1);
	ft_putstr_fd("exit\n", 1);
	cmd->exit_status[1] = 2;
	return (1);
}

int 	ft_exit(t_cmd *cmd, t_list **envs)
{
	int i;

	i = 0;
	cmd->exit_status[0] = 1;
	while (cmd->cmds[i] && !is_symbol(cmd->cmds[i]))
		i++;
	if (i == 1)
		return (first_case(cmd));
	if (ft_strlen(cmd->cmds[1]) > 20)
		return (fourth_case(cmd));
	if (!(ft_llatoi(cmd->cmds[1])))
		return (second_case(cmd));
	if (i > 2)
		return (third_case(cmd));
	cmd->exit_status[1] = (int)ft_llatoi(cmd->cmds[1]) % 256;
	ft_putstr_fd("exit\n", 1);
	return (1);
}
