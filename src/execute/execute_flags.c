/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_flags.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pantoine <pantoine@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 17:04:13 by pantoine          #+#    #+#             */
/*   Updated: 2024/05/10 23:19:10 by pantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execute.h"
#include "../../includes/evars.h"
#include "../../includes/minishell.h"

int	set_cmdargs_basevalues(t_lexer **lexer, int *lexer_pos, t_cmd *cmd)
{
	cmd->in = STDIN_FILENO;
	cmd->out = STDOUT_FILENO;
	cmd->tempfile_name = NULL;
	cmd->cmd_args = ft_lstnew(lexer[*lexer_pos]->content);
	if (!cmd->cmd_args)
	{
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
		malloc_exec_err();
		return (NULL);
	}
	if (set_cmdargs_basevalues(lexer, lexer_pos, cmd))
		return (NULL);
	*lexer_pos += 1;
	cmd->size_cmd = get_size_command(lexer, lexer_pos, cmd);
	if (cmd->size_cmd == -1)
	{
		free(cmd->cmd_args);
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
	newcmd_size = ft_lstnew(cmd);
	if (!newcmd_size)
	{
		free(cmd);
		malloc_exec_err();
		return (1);
	}
	ft_lstadd_back(cmds, newcmd_size);
	return (0);
}
