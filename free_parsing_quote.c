/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_parsing_quote.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erlajoua <erlajoua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 17:50:21 by erlajoua          #+#    #+#             */
/*   Updated: 2021/03/01 17:50:30 by erlajoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		free_quote(t_cmd *cmd, char *prompt, int index)
{
	free_char_double_array(cmd->cmds);
	free(prompt);
	return (index);
}
