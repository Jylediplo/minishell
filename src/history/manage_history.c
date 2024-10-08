/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_history.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lefabreg <lefabreg@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 12:35:45 by lefabreg          #+#    #+#             */
/*   Updated: 2024/06/02 11:22:38 by pantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/execute.h"

void	restore_history(t_history *history)
{
	char	*line;
	char	*word;

	history->fd = open("/tmp/.history", O_RDONLY | O_CREAT, 0644);
	if (history->fd == -1)
		return ((void)perror_context("open", ".history", 2));
	line = "init";
	while (line)
	{
		line = get_next_line(history->fd);
		if (line)
		{
			word = ft_strtrim(line, "\n");
			if (!word)
			{
				close(history->fd);
				return (free(line));
			}
			add_to_list(word, history);
			add_history(word);
			free(word);
		}
		free(line);
	}
	close(history->fd);
}
