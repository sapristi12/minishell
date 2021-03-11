/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_quotes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erlajoua <erlajoua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 17:58:57 by erlajoua          #+#    #+#             */
/*   Updated: 2021/03/03 09:08:49 by erlajoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		parsing_quotes(t_cmd *cmd, t_list **envs)
{
	int		i;

	i = 0;
	while (cmd->cmds[i])
	{
		if (!(is_even_quote(cmd->cmds[i])))
			return (0);
		if (!(cmd->cmds[i] = create_new_str(cmd->cmds[i], envs)))
			return (0);
		i++;
	}
	i = 0;
	while (cmd->cmds[i + 1])
		i++;
	if (!is_token_last(cmd))
		return (0);
	return (1);
}
