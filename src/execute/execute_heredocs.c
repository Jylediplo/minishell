/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_heredocs.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pantoine <pantoine@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 11:25:30 by pantoine          #+#    #+#             */
/*   Updated: 2024/05/09 12:17:36 by pantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execute.h"
#include "../../includes/get_next_line.h"
#include "../../includes/minishell.h"

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
		to_unlink = ft_strjoin(".hdtmp", nb_heredocs_str);
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

char	*name_tempfile(int current_temp)
{
	char		*name;
	char		*current_temp_str;

	current_temp_str = ft_itoa(current_temp);
	if (!current_temp_str)
		return (NULL);
	name = ft_strjoin(".hdtmp", current_temp_str);
	free(current_temp_str);
	return (name);
}

int	create_heredoc(char *delimiter, int *current_temp)
{
	int		tmp;
	char	*line;
	char	*tmp_filename;

	tmp_filename = name_tempfile(*current_temp);
	if (!tmp_filename)
		return (1);
	tmp = open(tmp_filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	free(tmp_filename);
	if (tmp == -1)
		return (2);
	*current_temp += 1;
	while (1)
	{
		write(1, "> ", 2);
		line = get_next_line(0);
		if (!ft_strncmp(line, delimiter, ft_strlen(delimiter))
			&& line[ft_strlen(delimiter)] == '\n')
		{
			free(line);
			break ;
		}
		write(tmp, line, ft_strlen(line));
		free(line);
	}
	close(tmp);
	return (0);
}
