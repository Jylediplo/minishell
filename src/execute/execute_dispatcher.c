/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_dispatcher.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lefabreg <lefabreg@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 16:34:22 by pantoine          #+#    #+#             */
/*   Updated: 2024/05/26 13:32:54 by pantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/evars.h"
#include "../../includes/execute.h"

int	no_command(t_cmd *cmd)
{
	int		saved_in;
	int		saved_out;

	if (save_standard_in_out(&saved_in, &saved_out))
		return (1);
	dup_redirections(cmd);
	reset_standard_in_out(saved_in, saved_out);
	return (0);
}

int	call_builtin(t_cmd *cmd, t_shell *shell, t_list *cmdlist, t_lexer **lexer)
{
	int		saved_out;
	int		saved_in;

	if (save_standard_in_out(&saved_in, &saved_out))
		return (1);
	if (dup_redirections(cmd))
	{
		close(saved_in);
		close(saved_out);
		return (1);
	}
	if (is_same_str(cmd->command[0], "exit"))
	{
		reset_standard_in_out(saved_in, saved_out);
		exit_petitcoq(cmd, cmdlist, lexer, shell);
	}
	else
		dispatch_builtin(cmd, shell);
	reset_standard_in_out(saved_in, saved_out);
	return (0);
}

static int	fork_it_all(t_cmd *cmd, t_shell *shell,
							t_list *cmdlist, t_lexer **lexer)
{
	pid_t	pid;
	int		pipe_fds[2];

	if (pipe(pipe_fds) == -1)
	{
		perror_context("pipe", NULL);
		if (shell->previous_pipe != -2)
		{
			while (wait(NULL) != -1)
				;
			close(shell->previous_pipe);
		}
		return (0);
	}
	pid = fork();
	if (!pid)
	{
		if (write_and_read_pipe(cmdlist, cmd->nb, shell, pipe_fds))
			free_all_exit(lexer, cmdlist, shell);
		executor(cmd, shell, cmdlist, lexer);
	}
	else if (pid == -1)
		return (fork_failure(pipe_fds, shell->previous_pipe));
	transfer_pipes(cmd, shell, cmdlist, pipe_fds);
	return (1);
}

int	dispatch_commands(t_list *cmdlist, t_shell *shell, t_lexer **lexer)
{
	t_list	*iter;
	t_cmd	*cmd;
	int		status;

	iter = cmdlist->next;
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
	while (waitpid(-1, &status, 0) != -1)
		continue ;
	if (WIFEXITED(status) && WEXITSTATUS(status) == 2)
		g_current_sig = 127;
	else if (WIFEXITED(status) && WEXITSTATUS(status) == 13)
		g_current_sig = 126;
	else if (WIFEXITED(status))
		g_current_sig = WEXITSTATUS(status);
	return (1);
}
