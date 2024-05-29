/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_dispatcher.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lefabreg <lefabreg@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 16:34:22 by pantoine          #+#    #+#             */
/*   Updated: 2024/05/29 15:15:19 by pantoine         ###   ########.fr       */
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
			free_all_exit(lexer, cmdlist, shell);
		executor(cmd, shell, cmdlist, lexer);
	}
	else if (shell->children[cmd->nb - 1].childprocess_pid == -1)
		return (fork_failure(shell->pipe_fds, shell->previous_pipe));
	transfer_pipes(cmd, shell, cmdlist, shell->pipe_fds);
	return (1);
}

void	wait_for_children(t_shell *shell, t_list *cmdlist)
{
	int		status;
	pid_t	pid;
	int		remaining_children;
	int		nb_cmd;
	int		i;

	i = 0;
	nb_cmd = ft_lstsize(cmdlist->next);
	remaining_children = nb_cmd;
	while (remaining_children > 0)
	{
		pid = waitpid(-1, &status, 0);
		if (pid == -1)
			break ;
		while (i < nb_cmd)
		{
			read_error_messages(shell, pid, i);
			i++;
		}
		i = 0;
		remaining_children--;
	}
	if (WIFEXITED(status) && WEXITSTATUS(status) == 2)
		g_current_sig = 127;
	else if (WIFEXITED(status) && WEXITSTATUS(status) == 13)
		g_current_sig = 126;
	else if (WIFEXITED(status))
		g_current_sig = WEXITSTATUS(status);
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
	wait_for_children(shell, cmdlist);
	return (1);
}
