/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_heredocs_termsettings.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pantoine <pantoine@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 19:31:21 by pantoine          #+#    #+#             */
/*   Updated: 2024/06/04 12:13:13 by pantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execute.h"
#include "../../includes/minishell.h"
#include "../../includes/evars.h"

static int	count_legal_chars(char *line)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (line[i])
	{
		if (line[i++] != '\034')
			count++;
	}
	return (count);
}

char	*ignore_ctrl_slash(char *line)
{
	int		i;
	int		j;
	int		count;
	char	*res;

	j = 0;
	count = count_legal_chars(line);
	res = malloc(sizeof(char) * (count + 1));
	if (!res)
	{
		perror_context("malloc", NULL, 2);
		return (NULL);
	}
	i = 0;
	while (line[i])
	{
		if (line[i] != '\034')
			res[j++] = line[i];
		i++;
	}
	res[j] = '\0';
	free(line);
	return (res);
}

int	write_to_tempfile(t_shell *shell, t_lexer *delimiter, int fd)
{
	char	*line;

	line = NULL;
	printf("delimiter: %s\n", delimiter->content);
	while (1)
	{
		line = custom_gnl(line);
		if (line)
		{
			line = ignore_ctrl_slash(line);
			if (!line)
				return (1);
		}
		if (gnl_line_handler(delimiter, line))
			return (0);
		else if (line)
			exp_hd(fd, line, shell->envp, delimiter->quote_removed);
	}
}

void	set_heredoc_attributes(struct termios og)
{
	struct termios	modified;

	modified = og;
	modified.c_lflag &= ~(ECHOCTL);
	modified.c_cc[VQUIT] = _POSIX_VDISABLE;
	modified.c_cc[VEOF] = 4;
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &modified);
}
