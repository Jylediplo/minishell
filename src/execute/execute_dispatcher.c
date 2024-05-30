/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_dispatcher.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyjy <jyjy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 16:34:22 by pantoine          #+#    #+#             */
/*   Updated: 2024/05/30 23:00:11 by pantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/evars.h"
#include "../../includes/execute.h"

int	no_command(t_cmd *cmd)
{
	int		saved_in;
	int		saved_out;

	if (save_standard_in_out(&saved_in, &saved_out, cmd->error_pipe[1]))
		return (1);
	dup_redirections(cmd);
	reset_standard_in_out(saved_in, saved_out, cmd->error_pipe[1]);
	return (0);
}

int	call_builtin(t_cmd *cmd, t_shell *shell, t_list *cmdlist, t_lexer **lexer)
{
	int		saved_out;
	int		saved_in;

	if (save_standard_in_out(&saved_in, &saved_out, cmd->error_pipe[1]))
		return (1);
	if (dup_redirections(cmd))
	{
		reset_standard_in_out(saved_in, saved_out, cmd->error_pipe[1]);
		return (1);
	}
	if (is_same_str(cmd->command[0], "exit"))
	{
		reset_standard_in_out(saved_in, saved_out, cmd->error_pipe[1]);
		exit_petitcoq(cmd, cmdlist, lexer, shell);
	}
	else
	{
		dispatch_builtin(cmd, shell);
		reset_standard_in_out(saved_in, saved_out, cmd->error_pipe[1]);
	}
	return (0);
}

static int	fork_it_all(t_cmd *cmd, t_shell *shell,
							t_list *cmdlist, t_lexer **lexer)
{
	if (pipe(shell->pipe_fds) == -1)
	{
		perror_context("pipe", NULL, 2);
		if (shell->previous_pipe != -2)
		{
			while (wait(NULL) != -1)
				;
			close(shell->previous_pipe);
		}
		return (0);
	}
	shell->children[cmd->nb - 1].childprocess_pid = fork();
	if (!shell->children[cmd->nb - 1].childprocess_pid)
	{
		close_unused_error_pipes(shell, cmdlist, cmd->nb);
		if (write_and_read_pipe(cmdlist, cmd->nb, shell, cmd))
			free_all_exit(lexer, cmdlist, shell, 1);
		executor(cmd, shell, cmdlist, lexer);
	}
	else if (shell->children[cmd->nb - 1].childprocess_pid == -1)
		return (fork_failure(shell->pipe_fds, shell->previous_pipe));
	transfer_pipes(cmd, shell, cmdlist, shell->pipe_fds);
	return (1);
}

int	dispatch_commands(t_list *cmdlist, t_shell *shell, t_lexer **lexer)
{
	t_list	*iter;
	t_cmd	*cmd;

	iter = cmdlist->next;
	if (create_error_pipes(cmdlist, shell))
		return (0);
	if (execute_one_command(cmdlist, shell, lexer))
		return (1);
	shell->previous_pipe = -2;
	while (iter)
	{
		cmd = iter->content;
		if (!fork_it_all(cmd, shell, cmdlist, lexer))
			return (0);
		iter = iter->next;
	}
	close_write_error_pipes(shell, cmdlist);
	signal(SIGINT, SIG_IGN);
	wait_for_children(shell, cmdlist);
	signal(SIGINT, SIG_DFL);
	return (1);
}
