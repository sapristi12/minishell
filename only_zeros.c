/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   only_zeros.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erlajoua <erlajoua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 17:45:17 by erlajoua          #+#    #+#             */
/*   Updated: 2021/03/12 10:09:35 by erlajoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		only_equal(char *str)
{
	int i;

	i = 0;
	while (str[i] && str[i] == '=')
		i++;
	if (str[i] == '\0')
		return (1);
	return (0);
}

int		only_zeros(char *str)
{
	int i;

	i = 0;
	while (str[i] && str[i] == '0')
		i++;
	if (str[i] == '\0')
		return (1);
	return (0);
}
