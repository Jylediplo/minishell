/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_errors.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pantoine <pantoine@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 18:06:02 by pantoine          #+#    #+#             */
/*   Updated: 2024/05/21 13:53:33 by pantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execute.h"

int	newcmd_malloc_err(t_cmd *cmd)
{
	perror_context("malloc", NULL);
	free_single_cmd(cmd->cmd_args);
	if (cmd->tempfile_name)
	{
		unlink(cmd->tempfile_name);
		free(cmd->tempfile_name);
	}
	free(cmd);
	return (1);
}

void	unexpected_token_exec_err(char *error_token)
{
	ft_putstr_fd("petitcoq: syntax error near unexpected token `", 2);
	ft_putstr_fd(error_token, 2);
	ft_putstr_fd("'\n", 2);
	g_current_sig = 2;
}

void	perror_context(char *failed_command, char *context)
{
	ft_putstr_fd("petitcoq: ", 2);
	ft_putstr_fd(failed_command, 2);
	ft_putstr_fd(": ", 2);
	if (is_same_str(failed_command, "malloc"))
		ft_putstr_fd("failure", 2);
	else
		ft_putstr_fd(strerror(errno), 2);
	if (context)
	{
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(context, 2);
	}
	ft_putstr_fd("\n", 2);
	//g_current_sig = errno;
}
