/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erlajoua <erlajoua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 17:53:46 by erlajoua          #+#    #+#             */
/*   Updated: 2021/03/01 20:18:33 by erlajoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_pwd(void)
{
	char	buffer[PATH_MAX];

	getcwd(buffer, PATH_MAX);
	ft_putstr_fd(buffer, STDOUT_FILENO);
	ft_putstr_fd("\n", STDOUT_FILENO);
	return (1);
}
