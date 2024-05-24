/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_flags_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pantoine <pantoine@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 12:05:25 by pantoine          #+#    #+#             */
/*   Updated: 2024/05/24 12:10:10 by pantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execute.h"

void	zero_cmdargs(t_cmd *cmd)
{
	cmd->in = NULL;
	cmd->out = NULL;
	cmd->tempfile_name = NULL;
	cmd->command = NULL;
	cmd->cmd_args = NULL;
}

int	delete_current_command(t_cmd *cmd)
{
	if (cmd->tempfile_name)
	{
		unlink(cmd->tempfile_name);
		free(cmd->tempfile_name);
	}
	free_single_cmd(cmd->cmd_args);
	free(cmd);
	return (0);
}
