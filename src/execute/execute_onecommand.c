/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_onecommand.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pantoine <pantoine@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 18:01:15 by pantoine          #+#    #+#             */
/*   Updated: 2024/05/17 16:34:21 by pantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/evars.h"
#include "../../includes/execute.h"

int	fork_one_command(t_cmd *cmd, t_shell *shell, t_list *cmdlist, t_lexer **lexer)
{
	pid_t	id;
	int		status;

	id = fork();
	if (!id)
	{
		pimped_execve(cmd, shell);
		free_all_exit(lexer, cmdlist, shell);
		return (1);
	}
	else if (id == -1)
	{
		perror_context("fork", NULL);
		free_all_exit(lexer, cmdlist, shell);
	}
	waitpid(-1, &status, 0);
	if (WEXITSTATUS(status) == 2)
		g_current_sig = 125 + WEXITSTATUS(status);
	return (0);
}

int	execute_one_command(t_list *cmdlist, t_shell *shell, t_lexer **lexer)
{
	t_cmd	*cmd;
	t_list	*current;
	
	if (ft_lstsize(cmdlist->next) > 1)
		return (0);
	current = cmdlist->next;
	cmd = current->content;
	if (!cmd->command[0])
	{
		no_command(cmd);
		return (1);
	}
	else if (is_builtin(cmd->command[0]))
		call_builtin(cmd, shell, cmdlist, lexer);
	else
		fork_one_command(cmd, shell, cmdlist, lexer);
	return (1);
}
