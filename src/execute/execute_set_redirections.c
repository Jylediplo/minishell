/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_set_redirections.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pantoine <pantoine@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 23:18:32 by pantoine          #+#    #+#             */
/*   Updated: 2024/05/19 12:57:57 by pantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execute.h"
#include "../../includes/evars.h"
#include "../../includes/minishell.h"

static int	redirect_stream(t_lexer **lexer, int *lexer_pos, t_cmd *cmd)
{
	if (lexer[*lexer_pos - 1]->e_flag == LESSER)
		cmd->in = lexer[*lexer_pos]->content;
	else if (lexer[*lexer_pos - 1]->e_flag == GREATER)
	{
		cmd->out = lexer[*lexer_pos]->content;
		/*open(lexer[*lexer_pos]->content,
				O_WRONLY | O_CREAT | O_TRUNC, 644);*/
	}
	else if (lexer[*lexer_pos - 1]->e_flag == APPEND)
		cmd->out = lexer[*lexer_pos]->content;
		/*cmd->out = open(lexer[*lexer_pos]->content,
				O_WRONLY | O_CREAT | O_APPEND, 644);*/
	return (0);
}

int	is_legal_token(t_lexer **lexer, int *lexer_pos, t_cmd *cmd)
{
	*lexer_pos += 1;
	if (lexer[*lexer_pos] && (lexer[*lexer_pos]->e_flag == WORD
			|| lexer[*lexer_pos]->e_flag == BUILTIN))
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

int	is_legal_heredoc(t_lexer **lexer, int *lexer_pos, t_cmd *cmd, t_list *envp)
{
	*lexer_pos += 1;
	if (lexer[*lexer_pos] && (lexer[*lexer_pos]->e_flag == WORD
			|| lexer[*lexer_pos]->e_flag == BUILTIN))
	{
		if (create_heredoc(lexer[*lexer_pos], cmd, envp))
			return (0);
		*lexer_pos += 1;
		return (1);
	}
	if (!lexer[*lexer_pos])
	{
		unexpected_token_exec_err("newline");
		return (0);
	}
	unexpected_token_exec_err(lexer[*lexer_pos]->content);
	*lexer_pos += 1;
	return (0);
}
