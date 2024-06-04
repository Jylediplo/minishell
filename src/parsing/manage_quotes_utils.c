/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_quotes_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pantoine <pantoine@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 12:40:43 by pantoine          #+#    #+#             */
/*   Updated: 2024/06/04 12:52:21 by pantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexing.h"
#include "../../includes/minishell.h"

static char	*init_cmd_pantoines_parser(t_quote *cmd, char *command)
{
	cmd->input_length = (int)ft_strlen(command);
	cmd->i = 0;
	cmd->quote_open = 0;
	cmd->output_index = 0;
	cmd->output = malloc(sizeof(char) * (cmd->input_length + 1));
	if (!cmd->output)
	{
		write(2, "petitcoq: malloc: failure\n", 26);
		return (NULL);
	}
	return (cmd->output);
}

char	*manage_quotes_pantoine(char *command, int *has_quotes)
{
	t_quote	cmd;

	init_cmd_pantoines_parser(&cmd, command);
	if (!cmd.output)
		return (NULL);
	while (cmd.i < cmd.input_length)
	{
		if (command[cmd.i] == '"' || command[cmd.i] == '\'')
		{
			*has_quotes = 1;
			current_is_quote(&cmd, command);
		}
		else
			current_is_not_quote(&cmd, command);
		cmd.i++;
	}
	if (cmd.quote_open)
	{
		free(cmd.output);
		write(2, "petitcoq: quotes: not closed\n", 29);
		return (NULL);
	}
	cmd.output[cmd.output_index] = '\0';
	return (cmd.output);
}
