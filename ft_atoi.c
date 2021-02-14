#include "minishell.h"

int 	ft_atoi(char *str)
{
	int i;
	int ret;
	int sign;

	sign = 1;
	i = 0;
	ret = 0;
	if (str[i] && (str[i] == '+' || str[i] == '-'))
	{
		if (str[i] && str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		ret = ret * 10 + str[i] - '0';
		i++;
	}
	return (ret * sign);
}
