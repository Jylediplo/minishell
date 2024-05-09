/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_flags.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pantoine <pantoine@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 17:04:13 by pantoine          #+#    #+#             */
/*   Updated: 2024/05/09 12:18:48 by pantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execute.h"
#include "../../includes/evars.h"
#include "../../includes/minishell.h"

int	add_size_arg_node(t_lexer **lexer, int *lexer_pos, t_list **cmds)
{
	static int	index = 0;
	t_cmd		*cmd;
	t_list		*newcmd_size;
	
	newcmd_size = NULL;
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
	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
	{
		malloc_exec_err();
		return (2);
	}
	cmd->size_cmd = get_size_command(lexer, lexer_pos, cmds);
	if (cmd->size_cmd == -1)
	{
		free(cmd);
		return (1);
	}
	printf("New command with size: <%d>\n", cmd->size_cmd);
	cmd->index = index++;
	cmd->in = "0";
	cmd->out = "1";
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

int	is_legal_token(t_lexer **lexer, int *lexer_pos, t_list *cmds)
{
	t_list	*current_cmd;
	t_cmd	*content_current_cmd;

	current_cmd = ft_lstlast(cmds);
	content_current_cmd = current_cmd->content;
	(void)content_current_cmd;
	*lexer_pos += 1;
	if (lexer[*lexer_pos] && (lexer[*lexer_pos]->flag == WORD
		|| lexer[*lexer_pos]->flag == BUILTIN))
	{
		printf("Valid token: <%s>\n", lexer[*lexer_pos]->content);
		*lexer_pos += 1;
		return (1);
	}
	unexpected_token_exec_err(lexer[*lexer_pos]->content);
	return (0);
}

int	is_legal_heredoc(t_lexer **lexer, int *lexer_pos, t_list *cmds)
{
	static int	current_temp = 0;
	int			heredoc_status;

	heredoc_status = 0;
	(void)cmds;
	*lexer_pos += 1;
	if (lexer[*lexer_pos] && lexer[*lexer_pos]->flag == WORD) //WILL HAVE TO BE DELIMITER
	{
		printf("Valid delimiter: <%s>\n", lexer[*lexer_pos]->content);
		heredoc_status = create_heredoc(lexer[*lexer_pos]->content, &current_temp);
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
