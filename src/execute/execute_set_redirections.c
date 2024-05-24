/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_set_redirections.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pantoine <pantoine@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 23:18:32 by pantoine          #+#    #+#             */
/*   Updated: 2024/05/24 11:51:32 by pantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execute.h"
#include "../../includes/evars.h"
#include "../../includes/minishell.h"

static int	add_outfile_node(t_cmd *cmd, t_lexer **lexer,
								int *lexer_pos, int outtype)
{
	t_outfile	*outfile;
	t_list		*new_outfile;

	outfile = malloc(sizeof(t_outfile));
	if (!outfile)
	{
		perror_context("malloc", NULL);
		return (1);
	}
	new_outfile = ft_lstnew(outfile);
	if (!new_outfile)
	{
		free(outfile);
		perror_context("malloc", NULL);
		return (1);
	}
	outfile = new_outfile->content;
	outfile->name = lexer[*lexer_pos]->content;
	outfile->outtype = outtype;
	ft_lstadd_back(&cmd->out, new_outfile);
	return (0);
}

static int	redirect_stream(t_lexer **lexer, int *lexer_pos, t_cmd *cmd)
{
	if (lexer[*lexer_pos - 1]->e_flag == LESSER)
		cmd->in = lexer[*lexer_pos]->content;
	else if (lexer[*lexer_pos - 1]->e_flag == GREATER)
	{
		if (add_outfile_node(cmd, lexer, lexer_pos, O_TRUNC))
			return (1);
	}
	else if (lexer[*lexer_pos - 1]->e_flag == APPEND)
	{
		if (add_outfile_node(cmd, lexer, lexer_pos, O_APPEND))
			return (1);
	}
	return (0);
}

int	is_legal_token(t_lexer **lexer, int *lexer_pos, t_cmd *cmd)
{
	*lexer_pos += 1;
	if (lexer[*lexer_pos] && (lexer[*lexer_pos]->e_flag == WORD
			|| lexer[*lexer_pos]->e_flag == BUILTIN))
	{
		if (redirect_stream(lexer, lexer_pos, cmd))
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
