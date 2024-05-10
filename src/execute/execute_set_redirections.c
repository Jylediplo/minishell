/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_set_redirections.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pantoine <pantoine@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 23:18:32 by pantoine          #+#    #+#             */
/*   Updated: 2024/05/10 23:24:02 by pantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execute.h"
#include "../../includes/evars.h"
#include "../../includes/minishell.h"

int	redirect_stream(t_lexer **lexer, int *lexer_pos, t_cmd *cmd)
{
	if (lexer[*lexer_pos - 1]->flag == LESSER)
	{
		cmd->in = open(lexer[*lexer_pos]->content, O_RDONLY);
		if (cmd->in == -1)
			perror("open");
	}
	else if (lexer[*lexer_pos - 1]->flag == GREATER)
	{
		cmd->out = open(lexer[*lexer_pos]->content, O_WRONLY | O_TRUNC);
		if (cmd->out == -1)
			perror("open");
	}
	else if (lexer[*lexer_pos - 1]->flag == APPEND)
	{
		cmd->out = open(lexer[*lexer_pos]->content,
				O_WRONLY | O_CREAT | O_APPEND, 644);
		if (cmd->out == -1)
			perror("open");
	}
	return (0);
}

int	is_legal_token(t_lexer **lexer, int *lexer_pos, t_cmd *cmd)
{
	*lexer_pos += 1;
	if (lexer[*lexer_pos] && (lexer[*lexer_pos]->flag == WORD
			|| lexer[*lexer_pos]->flag == BUILTIN))
	{
		redirect_stream(lexer, lexer_pos, cmd);
		*lexer_pos += 1;
		return (1);
	}
	if (!lexer[*lexer_pos])
	{
		unexpected_token_exec_err("newline");
		return (0);
	}
	unexpected_token_exec_err(lexer[*lexer_pos]->content);
	return (0);
}

int	is_legal_heredoc(t_lexer **lexer, int *lexer_pos, t_cmd *cmd)
{
	static int	current_temp = 0;
	int			heredoc_status;

	heredoc_status = 0;
	*lexer_pos += 1;
	if (lexer[*lexer_pos] && (lexer[*lexer_pos]->flag == WORD
			|| lexer[*lexer_pos]->flag == BUILTIN))
	{
		heredoc_status = create_heredoc(lexer[*lexer_pos]->content, cmd);
		if (heredoc_status == 1)
		{
			malloc_exec_err();
			return (0);
		}
		else if (heredoc_status == 2)
		{
			delete_heredocs(current_temp);
			return (0);
		}
		*lexer_pos += 1;
		return (1);
	}
	unexpected_token_exec_err(lexer[*lexer_pos]->content);
	*lexer_pos += 1;
	return (0);
}
