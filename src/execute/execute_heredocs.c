/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_heredocs.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pantoine <pantoine@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 11:25:30 by pantoine          #+#    #+#             */
/*   Updated: 2024/06/02 17:05:07 by pantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execute.h"
#include "../../includes/get_next_line.h"
#include "../../includes/minishell.h"
#include "../../includes/evars.h"
#include <limits.h>

static void	sanitise_tempfile_name(t_cmd *cmd)
{
	int		i;

	i = 11;
	if (!cmd->tempfile_name)
		return ;
	while (cmd->tempfile_name[i])
	{
		if (cmd->tempfile_name[i] == '/')
			cmd->tempfile_name[i] = '_';
		i++;
	}
}

static char	*release_prev_tempfile(t_cmd *cmd, char random[11])
{
	char	*name;

	random[10] = '\0';
	name = ft_strjoin(HDNAME, random);
	if (cmd->tempfile_name)
	{
		custom_unlink(cmd->tempfile_name);
		free(cmd->tempfile_name);
		cmd->tempfile_name = NULL;
	}
	if (!name)
		perror_context("malloc", NULL, 2);
	return (name);
}

static char	*name_tempfile(t_cmd *cmd)
{
	char	*name;
	char	random[11];
	int		random_fd;
	ssize_t	count;

	random_fd = open("/dev/urandom", O_RDONLY);
	if (random_fd == -1)
	{
		perror_context("open", "/dev/urandom", 2);
		return (NULL);
	}
	count = read(random_fd, random, 11);
	close(random_fd);
	if (count == -1)
	{
		perror_context("read", "/dev/urandom", 2);
		return (NULL);
	}
	name = release_prev_tempfile(cmd, random);
	cmd->tempfile_name = name;
	sanitise_tempfile_name(cmd);
	return (cmd->tempfile_name);
}

static int	open_temp(char *filename, t_cmd *cmd)
{
	int	fd;

	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror_context("open", filename, 2);
		free(filename);
		cmd->tempfile_name = NULL;
	}
	else
		cmd->in = filename;
	return (fd);
}

int	create_heredoc(t_lexer *delimiter, t_cmd *cmd, t_shell *shell)
{
	int				tmp_fd;
	char			*line;
	char			*tmp_filename;

	tmp_filename = name_tempfile(cmd);
	if (!tmp_filename)
		return (1);
	tmp_fd = open_temp(tmp_filename, cmd);
	if (tmp_fd == -1)
		return (1);
	handle_signals(SIG_HD);
	line = NULL;
	while (1)
	{
		line = custom_gnl(line);
		if (gnl_line_handler(delimiter, line))
			break ;
		else if (line)
			exp_hd(tmp_fd, line, shell->envp, delimiter->quote_removed);
	}
	handle_signals(SIG_FG);
	close(tmp_fd);
	if (g_current_sig == 130)
		return (1);
	return (0);
}
