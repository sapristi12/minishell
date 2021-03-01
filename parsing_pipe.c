/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erlajoua <erlajoua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 17:58:38 by erlajoua          #+#    #+#             */
/*   Updated: 2021/03/01 17:59:16 by erlajoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		parsing_pipe(t_cmd *cmd)
{
	cmd->pipe.nb_pipe = count_string(cmd->cmds, "|");
	cmd->pipe.save = cmd->pipe.nb_pipe;
	return (1);
}
