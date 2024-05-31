/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_heredocs_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pantoine <pantoine@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 22:33:58 by pantoine          #+#    #+#             */
/*   Updated: 2024/05/31 18:57:04 by pantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execute.h"
#include "../../includes/minishell.h"
#include "../../includes/evars.h"

char	*custom_gnl(char *line)
{
	char	*res;

	if (errno != EINTR || (errno == EINTR && line))
		write(1, "> ", 2);
	res = get_next_line(STDIN_FILENO);
	return (res);
}

void	custom_unlink(char *to_unlink)
{
	if (unlink(to_unlink) == -1)
		perror_context("unlink", NULL, 2);
}

int	gnl_line_handler(t_lexer *delimiter, char *line)
{
	if (!line && errno != EINTR)
	{
		printf("\npetitcoq: warning: here-document delimited ");
		printf("by end-of-file (wanted `%s')\n", delimiter->content);
		return (1);
	}
	else if (errno == EINTR && g_current_sig == 130 && !line)
		return (1);
	else if (errno == EINTR && g_current_sig == 131 && !line)
		return (0);
	if (!ft_strncmp(line, delimiter->content, ft_strlen(delimiter->content))
		&& line[ft_strlen(delimiter->content)] == '\n')
	{
		free(line);
		return (1);
	}
	return (0);
}

static int	start_dollar_sequence(int fd, char *input, int *i, t_list *envp)
{
	int		j;
	int		index;
	char	*to_expand;
	char	*expanded;

	*i += 1;
	j = *i;
	index = 0;
	while (valid_identifier_char(input[*i]))
		*i += 1;
	to_expand = malloc(sizeof(char *) * (*i - j + 1));
	if (!to_expand)
	{
		perror_context("malloc", NULL, 2);
		return (1);
	}
	while (valid_identifier_char(input[j]))
		to_expand[index++] = input[j++];
	to_expand[index] = '\0';
	expanded = get_envvar_value(&envp, to_expand);
	if (expanded)
		write(fd, expanded, ft_strlen(expanded));
	free(to_expand);
	return (0);
}

int	exp_hd(int fd, char *input, t_list *envp, int noexpand)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] == '$' && !noexpand)
			start_dollar_sequence(fd, input, &i, envp);
		else
			write(fd, &input[i++], 1);
	}
	free(input);
	return (0);
}
