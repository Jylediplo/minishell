/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_flags_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pantoine <pantoine@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 12:05:25 by pantoine          #+#    #+#             */
/*   Updated: 2024/05/30 14:43:50 by pantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execute.h"

void	zero_cmdargs(t_cmd *cmd)
{
	cmd->in = NULL;
	cmd->out = NULL;
	cmd->tempfile_name = NULL;
	cmd->command = NULL;
	cmd->cmd_args = NULL;
}

int	delete_current_command(t_cmd *cmd)
{
	if (cmd->tempfile_name)
	{
		custom_unlink(cmd->tempfile_name);
		free(cmd->tempfile_name);
	}
	if (cmd->cmd_args)
		free_single_cmd(cmd->cmd_args);
	free(cmd);
	return (0);
}

int	flag_redirect_stream(t_lexer **lexer, int *lexer_pos)
{
	if (lexer[*lexer_pos]->e_flag == APPEND
		|| lexer[*lexer_pos]->e_flag == GREATER
		|| lexer[*lexer_pos]->e_flag == LESSER)
		return (1);
	return (0);
}

int	flag_add_to_node(t_lexer **lexer, int *lexer_pos)
{
	if (lexer[*lexer_pos]->e_flag == WORD
		|| lexer[*lexer_pos]->e_flag == PIPE
		|| lexer[*lexer_pos]->e_flag == BUILTIN)
		return (1);
	return (0);
}
