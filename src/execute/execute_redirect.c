/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_redirect.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pantoine <pantoine@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 00:32:39 by pantoine          #+#    #+#             */
/*   Updated: 2024/05/20 00:12:15 by pantoine         ###   ########.fr       */
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

int	write_and_read_pipe(t_list *cmdlist, int nb_cmd, t_shell *shell, int pipe_fds[2])
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

static int	redirect_output(t_cmd *cmd)
{
	int			fd;
	t_list		*iter;
	t_outfile	*outfile;

	iter = cmd->out;
	while (iter)
	{
		outfile = iter->content;
		fd = open(outfile->name,
				O_WRONLY | O_CREAT | outfile->outtype, 0644);
		if (fd == -1)
		{
			perror_context("open", outfile->name);
			return (1);
		}
		iter = iter->next;
		if (iter)
			close(fd);
	}
	if (dup2(fd, 1) == -1)
	{
		close(fd);
		perror_context("dup2", NULL);
		return (1);
	}
	close(fd);
	return (0);
}

static int	redirect_input(t_cmd *cmd)
{
	int	fd;

	fd = open(cmd->in, O_RDONLY);
	if (fd == -1)
	{
		perror_context("open", cmd->in);
		return (1);
	}
	if (dup2(fd, 0) == -1)
	{
		close(fd);
		perror_context("dup2", NULL);
		return (1);
	}
	close(fd);
	return (0);
}

int	dup_redirections(t_cmd *cmd)
{
	if (cmd->in)
	{
		if (redirect_input(cmd))
			return (1);
	}
	if (cmd->out)
	{
		if (redirect_output(cmd))
			return (1);
	}
	return (0);
}
