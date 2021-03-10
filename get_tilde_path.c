/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_tilde_path.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erlajoua <erlajoua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 19:05:32 by erlajoua          #+#    #+#             */
/*   Updated: 2021/03/10 15:31:11 by erlajoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_tilde_path(char *str, t_list **envs)
{
	int		i;
	char	*dest;
	char	*tmp;

	i = 0;
	tmp = get_env(*envs, "HOME");
	if (!tmp)
		return (NULL);
	dest = ft_strdup(tmp);
	if (!dest)
		return (NULL);
	while (*str && *str != '~')
		str++;
	str++;
	while (str[i])
	{
		dest = char_strjoin(dest, str[i]);
		i++;
	}
	return (dest);
}
