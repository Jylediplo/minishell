/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_heredocs.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pantoine <pantoine@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 11:25:30 by pantoine          #+#    #+#             */
/*   Updated: 2024/05/14 01:35:29 by pantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execute.h"
#include "../../includes/get_next_line.h"
#include "../../includes/minishell.h"
#include <limits.h>

void	sanitise_tempfile_name(t_cmd *cmd)
{
	int	i;

	i = 0;
	if (!cmd->tempfile_name)
		return ;
	while (cmd->tempfile_name[i])
	{
		if (cmd->tempfile_name[i] == '/')
			cmd->tempfile_name[i] = '_';
		i++;
	}
}

char	*name_tempfile(t_cmd *cmd)
{
	char	*name;
	char	random[11];
	int		random_fd;
	ssize_t	count;

	random_fd = open("/dev/urandom", O_RDONLY);
	if (random_fd == -1)
	{
		perror_context("open", "/dev/urandom");
		return (NULL);
	}
	count = read(random_fd, random, 11);
	close(random_fd);
	if (count == -1)
	{
		perror_context("read", "/dev/urandom");
		return (NULL);
	}
	random[10] = '\0';
	name = ft_strjoin(HDNAME, random);
	cmd->tempfile_name = name;
	if (!name)
		perror_context("malloc", NULL);
	sanitise_tempfile_name(cmd);
	return (name);
}

int	open_temp(char *filename, t_cmd *cmd)
{
	int	fd;

	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror_context("open", filename);
		free(filename);
		cmd->tempfile_name = NULL;
	}
	return (fd);
}

int	create_heredoc(char *delimiter, t_cmd *cmd)
{
	int		tmp_fd;
	char	*line;
	char	*tmp_filename;

	tmp_filename = name_tempfile(cmd);
	if (!tmp_filename)
		return (1);
	tmp_fd = open_temp(tmp_filename, cmd);
	if (tmp_fd == -1)
		return (1);
	cmd->in = tmp_filename;
	while (1)
	{
		write(1, "> ", 2);
		line = get_next_line(STDIN_FILENO);
		if (!ft_strncmp(line, delimiter, ft_strlen(delimiter))
			&& line[ft_strlen(delimiter)] == '\n')
		{
			free(line);
			break ;
		}
		write(tmp_fd, line, ft_strlen(line));
		free(line);
	}
	close(tmp_fd);
	return (0);
}
