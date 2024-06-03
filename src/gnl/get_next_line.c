/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lefabreg <lefabreg@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 16:57:21 by lefabreg          #+#    #+#             */
/*   Updated: 2024/06/03 13:26:02 by pantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*manage_line_with_n_for_buffer(char *buffer, size_t index)
{
	size_t	i;
	char	*line;
	char	*temp;

	line = malloc(sizeof(char) * index + 1);
	if (!line)
		return (NULL);
	i = -1;
	while (++i < index)
		line[i] = buffer[i];
	line[i] = '\0';
	temp = ft_substr(buffer, index, BUFFER_SIZE);
	if (!temp)
		return (NULL);
	i = -1;
	while (temp[++i])
		buffer[i] = temp[i];
	while (buffer[i])
		buffer[i++] = '\0';
	return (free(temp), line);
}

char	*manage_line_with_n_for_line(char *buffer, size_t index)
{
	size_t	i;
	char	*line;
	char	*temp;
	char	*test;

	if (!index)
		return (NULL);
	line = malloc(sizeof(char) * index + 1);
	if (!line)
		return (NULL);
	i = 0;
	while (i < index)
	{
		line[i] = buffer[i];
		i++;
	}
	line[i] = '\0';
	test = buffer;
	temp = ft_substr(buffer, index, BUFFER_SIZE);
	free(test);
	if (!temp)
		return (NULL);
	return (free(temp), line);
}

char	*read_line(int fd, char *buffer, char *previous_line, int *bytes_read)
{
	char	*line;
	char	*temp;
	size_t	i;

	i = 0;
	if (previous_line)
	{
		temp = ft_strdup(previous_line);
		free(previous_line);
	}
	else
		temp = ft_strdup(buffer);
	while (buffer[i])
		buffer[i++] = '\0';
	*bytes_read = read(fd, buffer, BUFFER_SIZE);
	if (*bytes_read == 0 && temp)
		return (line = ft_strjoin(temp, buffer), *bytes_read = 0, free(temp),
			line);
	if (*bytes_read <= 0)
		return (*bytes_read = 0, free(temp), NULL);
	line = ft_strjoin(temp, buffer);
	if (!line || !temp)
		return (NULL);
	return (free(temp), line);
}

char	*helper(int fd, char *buffer, int bytes_read)
{
	char	*line;
	char	*temp;

	line = NULL;
	if (check_eof(buffer, bytes_read))
		return (NULL);
	while (!index_for_n(line) && bytes_read > 0)
	{
		line = read_line(fd, buffer, line, &bytes_read);
		if (!line)
			return (NULL);
	}
	if (bytes_read == 0)
		return (line);
	line = manage_line_with_n_for_line(line, index_for_n(line));
	temp = manage_line_with_n_for_buffer(buffer, index_for_n(buffer));
	if (!temp)
		return (NULL);
	free(temp);
	return (line);
}

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE + 1];
	char		*line;
	int			bytes_read;

	bytes_read = 1;
	line = NULL;
	if (!buffer[0])
		bytes_read = read(fd, buffer, BUFFER_SIZE);
	if (bytes_read <= 0 || fd < 0)
		return (NULL);
	if (index_for_n(buffer))
		line = manage_line_with_n_for_buffer(buffer, index_for_n(buffer));
	else
		line = helper(fd, buffer, bytes_read);
	if (!line)
		return (NULL);
	return (line);
}
