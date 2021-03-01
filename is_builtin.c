/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erlajoua <erlajoua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 20:21:25 by erlajoua          #+#    #+#             */
/*   Updated: 2021/03/01 20:22:22 by erlajoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		is_builtin(char *str)
{
	if (!(ft_strcmp(str, "pwd")))
		return (1);
	if (!(ft_strcmp(str, "echo")))
		return (1);
	if (!(ft_strcmp(str, "env")))
		return (1);
	if (!(ft_strcmp(str, "cd")))
		return (1);
	if (!ft_strcmp(str, "export"))
		return (1);
	if (!(ft_strcmp(str, "unset")))
		return (1);
	if (!(ft_strcmp(str, "exit")))
		return (1);
	return (0);
}
