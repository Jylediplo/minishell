/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_redirect.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pantoine <pantoine@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 00:32:39 by pantoine          #+#    #+#             */
/*   Updated: 2024/05/26 12:35:24 by pantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/evars.h"
#include "../../includes/execute.h"

static int	redirect_output(t_cmd *cmd)
{
	int			fd;
	t_list		*iter;
	t_outfile	*outfile;

	iter = cmd->out;
	while (iter)
	{
		outfile = iter->content;
		fd = open_outfile(outfile);
		if (fd == -1)
			return (1);
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
