/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_heredocs.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pantoine <pantoine@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 11:25:30 by pantoine          #+#    #+#             */
/*   Updated: 2024/05/10 22:00:17 by pantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execute.h"
#include "../../includes/get_next_line.h"
#include "../../includes/minishell.h"
#include <limits.h>

int	delete_heredocs(int nb_heredocs)
{
	char	*to_unlink;
	char	*nb_heredocs_str;
	int		index;

	index = 0;
	while (index <= nb_heredocs)
	{
		nb_heredocs_str = ft_itoa(index);
		if (!nb_heredocs_str)
			return (1);
		to_unlink = ft_strjoin(HDNAME, nb_heredocs_str);
		if (!to_unlink)
		{
			free(nb_heredocs_str);
			continue ;
		}
		unlink(to_unlink);
		free(nb_heredocs_str);
		free(to_unlink);
	}
	return (0);
}

char	*name_tempfile(t_cmd *cmd)
{
	char	*name;
	char	random[11];
	int		random_fd;
	ssize_t	count;

	random_fd = open("/dev/urandom", O_RDONLY);
	if (random_fd == -1)
		return (NULL);
	count = read(random_fd, random, 11);
	random[10] = '\0';
	close(random_fd);
	if (count == -1)
		return (NULL);
	name = ft_strjoin(HDNAME, random);
	cmd->tempfile_name = name;
	return (name);
}

int	create_heredoc(char *delimiter, t_cmd *cmd)
{
	int		tmp;
	char	*line;
	char	*tmp_filename;

	tmp_filename = name_tempfile(cmd);
	if (!tmp_filename)
		return (1);
	tmp = open(tmp_filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (tmp == -1)
		return (2);
	cmd->in = tmp;
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
		write(tmp, line, ft_strlen(line));
		free(line);
	}
	return (0);
}
