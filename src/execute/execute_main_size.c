/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_main_size.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pantoine <pantoine@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 23:52:18 by pantoine          #+#    #+#             */
/*   Updated: 2024/05/24 18:52:26 by pantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execute.h"
#include "../../includes/evars.h"
#include "../../includes/minishell.h"

int	add_arg_to_cmd(int *lexer_pos, t_cmd *cmd, char *newarg_content)
{
	t_list	*new_arg;

	new_arg = ft_lstnew(newarg_content);
	if (!new_arg)
	{
		perror_context("malloc", NULL);
		return (1);
	}
	ft_lstadd_back(&cmd->cmd_args, new_arg);
	(*lexer_pos)++;
	return (0);
}

static int	filter_type_input(t_lexer **lexer, int *lexer_pos,
						t_list **cmds, t_list *envp)
{
	t_cmd	*cmd;
	t_list	*current_cmd;

	current_cmd = ft_lstlast(*cmds);
	cmd = current_cmd->content;
	if (flag_add_to_node(lexer, lexer_pos))
	{
		if (add_size_arg_node(lexer, lexer_pos, cmds, envp))
			return (1);
	}
	else if (lexer[*lexer_pos]->e_flag == HEREDOC
		|| flag_redirect_stream(lexer, lexer_pos))
	{
		if (!cmd->command)
		{
			if (add_size_arg_node(lexer, lexer_pos, cmds, envp))
				return (1);
		}
	}
	return (0);
}

int	free_lex_cmdlist(t_lexer **lexer, t_list *cmdlist)
{
	free_lexer(lexer);
	free_cmdlist(cmdlist);
	return (0);
}

int	get_cmdlist(t_lexer **lexer, t_shell *shell)
{
	int		i;
	t_list	*head;

	i = 0;
	head = init_cmdlist_size();
	if (!head)
	{
		free_lexer(lexer);
		return (1);
	}
	lexer = init_lex(shell->envp, lexer);
	if (!lexer)
	{
		free_cmdlist(head);
		return (1);
	}
	while (lexer[i])
	{
		if (filter_type_input(lexer, &i, &head, shell->envp) == 1)
			return (free_lex_cmdlist(lexer, head));
	}
	if (copy_all_cmds(head->next))
		return (free_lex_cmdlist(lexer, head));
	dispatch_commands(head, shell, lexer);
	free_lexer(lexer);
	free_command_arrays(head);
	free_cmdlist(head);
	return (0);
}
