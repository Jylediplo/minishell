/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_redirect_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pantoine <pantoine@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 11:47:49 by pantoine          #+#    #+#             */
/*   Updated: 2024/05/24 11:50:16 by pantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/evars.h"
#include "../../includes/execute.h"

int	transfer_pipes(t_cmd *cmd, t_shell *shell, t_list *cmdlist, int pipe_fds[2])
{
	if (cmd->nb > 1)
		close(shell->previous_pipe);
	if (cmd->nb == ft_lstsize(cmdlist->next))
		close(pipe_fds[0]);
	close(pipe_fds[1]);
	shell->previous_pipe = pipe_fds[0];
	return (0);
}

int	write_and_read_pipe(t_list *cmdlist, int nb_cmd,
							t_shell *shell, int pipe_fds[2])
{
	if (nb_cmd > 1)
	{
		if (dup2(shell->previous_pipe, 0) == -1)
		{
			close(pipe_fds[0]);
			close(pipe_fds[1]);
			perror_context("dup2", NULL);
			return (1);
		}
		close(shell->previous_pipe);
	}
	if (nb_cmd != ft_lstsize(cmdlist->next))
	{
		if (dup2(pipe_fds[1], 1) == -1)
		{
			close(pipe_fds[0]);
			close(pipe_fds[1]);
			perror_context("dup2", NULL);
			return (1);
		}
	}
	close(pipe_fds[0]);
	close(pipe_fds[1]);
	return (0);
}

int	open_outfile(t_outfile *outfile)
{
	int	fd;

	fd = open(outfile->name,
			O_WRONLY | O_CREAT | outfile->outtype, 0644);
	if (fd == -1)
		perror_context("open", outfile->name);
	return (fd);
}
