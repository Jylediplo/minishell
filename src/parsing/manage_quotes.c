/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lefabreg <lefabreg@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 14:04:58 by lefabreg          #+#    #+#             */
/*   Updated: 2024/05/16 14:34:54 by lefabreg         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexing.h"
#include "../../includes/minishell.h"

void	init_cmd(t_quote *cmd, char *command)
{
	cmd->input_length = (int)ft_strlen(command);
	cmd->i = 0;
	cmd->quote_open = 0;
	cmd->output_index = 0;
	cmd->output = malloc(sizeof(char) * (cmd->input_length + 1));
	if (!cmd->output)
	{
		printf("Memory allocation failed.\n");
		exit(1);
	}
}

int	check_quotes(char *command, t_list *envp)
{
	char	*quotes;

	quotes = manage_quotes(command);
	if (!quotes)
	{
		free_envp(envp);
		free(command);
		printf("Error malloc !\n");
		exit(1);
	}
	if (quotes)
	{
		free(quotes);
		return (1);
	}
	return (0);
}
void	current_is_quote(t_quote *cmd, char *command)
{
	if (!cmd->quote_open)
	{
		cmd->quote_open = 1;
		cmd->current_quote = command[cmd->i];
	}
	else if (cmd->current_quote == command[cmd->i])
		cmd->quote_open = 0;
	else
		cmd->output[cmd->output_index++] = command[cmd->i];
}

void	current_is_not_quote(t_quote *cmd, char *command)
{
	if (cmd->quote_open)
	{
		cmd->output[cmd->output_index++] = command[cmd->i];
	}
	else if (command[cmd->i] != ' ')
	{
		cmd->output[cmd->output_index++] = command[cmd->i];
	}
	else
	{
		if (cmd->output_index > 0 && cmd->output[cmd->output_index - 1] != ' ')
		{
			cmd->output[cmd->output_index++] = command[cmd->i];
		}
	}
}

char	*manage_quotes(char *command)
{
	t_quote	cmd;

	init_cmd(&cmd, command);
	while (cmd.i < cmd.input_length)
	{
		if (command[cmd.i] == '"' || command[cmd.i] == '\'')
			current_is_quote(&cmd, command);
		else
			current_is_not_quote(&cmd, command);
		cmd.i++;
	}
	if (cmd.quote_open)
	{
		free(cmd.output);
		printf("Error: Quote not properly closed.\n");
		return (NULL);
	}
	cmd.output[cmd.output_index] = '\0';
	return (cmd.output);
}
