/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_errors.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pantoine <pantoine@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 18:06:02 by pantoine          #+#    #+#             */
/*   Updated: 2024/05/28 16:38:31 by pantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execute.h"

int	newcmd_malloc_err(t_cmd *cmd)
{
	perror_context("malloc", NULL, 2);
	free_single_cmd(cmd->cmd_args);
	if (cmd->tempfile_name)
	{
		custom_unlink(cmd->tempfile_name);
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

void	perror_context(char *failed_command, char *context, int fd)
{
	ft_putstr_fd("petitcoq: ", fd);
	ft_putstr_fd(failed_command, fd);
	ft_putstr_fd(": ", fd);
	if (is_same_str(failed_command, "malloc"))
		ft_putstr_fd("failure", fd);
	else
		ft_putstr_fd(strerror(errno), fd);
	if (context)
	{
		ft_putstr_fd(": ", fd);
		ft_putstr_fd(context, fd);
	}
	ft_putstr_fd("\n", fd);
	if (!is_same_str(failed_command, "execve"))
		g_current_sig = 1;
	else
	{
		if (errno == 2 && !g_current_sig)
			g_current_sig = 2;
		else if (errno == 13 && !g_current_sig)
			g_current_sig = 13;
	}
}
