/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_flags.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pantoine <pantoine@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 17:04:13 by pantoine          #+#    #+#             */
/*   Updated: 2024/05/13 23:11:41 by pantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execute.h"
#include "../../includes/evars.h"
#include "../../includes/minishell.h"

int	get_size_command(t_lexer **lexer, int *lexer_pos, t_cmd *cmd)
{
	while (lexer[*lexer_pos] && lexer[*lexer_pos]->flag != PIPE)
	{
		if (lexer[*lexer_pos]->flag == WORD
			|| lexer[*lexer_pos]->flag == BUILTIN)
		{
			if (add_arg_to_cmd(lexer_pos, cmd, lexer[*lexer_pos]->content))
				return (-1);
		}
		else if (flag_redirect_stream(lexer, lexer_pos))
		{
			if (!is_legal_token(lexer, lexer_pos, cmd))
				return (-1);
		}
		else if (lexer[*lexer_pos]->flag == HEREDOC)
		{
			if (!is_legal_heredoc(lexer, lexer_pos, cmd))
				return (-1);
		}
		if (!lexer[*lexer_pos])
			return (0);
		if (lexer[*lexer_pos]->flag == PIPE)
			break ;
	}
	return (0);
}

int	set_cmdargs_basevalues(t_lexer **lexer, int *lexer_pos, t_cmd *cmd)
{
	cmd->in = NULL;
	cmd->out = NULL;
	cmd->tempfile_name = NULL;
	cmd->command = NULL;
	cmd->cmd_args = ft_lstnew(lexer[*lexer_pos]->content);
	if (!cmd->cmd_args)
	{
		perror_context("malloc", NULL);
		free(cmd);
		return (1);
	}
	return (0);
}

t_cmd	*init_cmdargs(t_lexer **lexer, int *lexer_pos)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
	{
		perror_context("malloc", NULL);
		return (NULL);
	}
	if (set_cmdargs_basevalues(lexer, lexer_pos, cmd))
		return (NULL);
	*lexer_pos += 1;
	if (get_size_command(lexer, lexer_pos, cmd) == -1)
	{
		if (cmd->tempfile_name)
		{
			unlink(cmd->tempfile_name);
			free(cmd->tempfile_name);
		}
		free_single_cmd(cmd->cmd_args);
		free(cmd);
		return (NULL);
	}
	return (cmd);
}

int	add_size_arg_node(t_lexer **lexer, int *lexer_pos, t_list **cmds)
{
	t_cmd	*cmd;
	t_list	*newcmd_size;

	if (lexer[*lexer_pos]->flag == PIPE)
	{
		*lexer_pos += 1;
		if (lexer[*lexer_pos] && (lexer[*lexer_pos]->flag != WORD
				&& lexer[*lexer_pos]->flag != BUILTIN))
		{
			unexpected_token_exec_err(lexer[*lexer_pos]->content);
			return (1);
		}
	}
	cmd = init_cmdargs(lexer, lexer_pos);
	if (!cmd)
		return (1);
	newcmd_size = ft_lstnew(cmd);
	if (!newcmd_size)
		return (newcmd_malloc_err(cmd));
	ft_lstadd_back(cmds, newcmd_size);
	return (0);
}
