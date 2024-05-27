/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_dispatcher.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lefabreg <lefabreg@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 16:34:22 by pantoine          #+#    #+#             */
/*   Updated: 2024/05/27 18:48:46 by pantoine         ###   ########.fr       */
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
		dispatch_builtin(cmd, shell);
	reset_standard_in_out(saved_in, saved_out, cmd->error_pipe[1]);
	return (0);
}

static int	create_error_pipes(t_list *cmdlist, t_shell *shell)
{
	t_list	*iter;
	int		i;

	iter = cmdlist->next;
	i = 0;
	shell->error_pipes = malloc(sizeof(int *) * ft_lstsize(iter));
	if (!shell->error_pipes)
	{
		perror_context("malloc", NULL);
		if (shell->previous_pipe != -2)
			close(shell->previous_pipe);
		return (0);
	}
	while (iter)
	{
		shell->error_pipes[i] = malloc(sizeof(int) * 2);
		if (pipe(shell->error_pipes[i++]) == -1)
		{
			free(shell->error_pipes);
			perror_context("pipe", NULL);
			return (1);
		}
		iter = iter->next;
	}
	return (0);
}

static void	close_write_error_pipes(t_shell *shell, t_list *cmdlist)
{
	int	i;

	i = ft_lstsize(cmdlist->next) - 1;
	while (i >= 0)
		close(shell->error_pipes[i--][1]);
}

static int	read_error_messages(t_shell *shell, t_list *cmdlist)
{
	char	*err_msg;
	int		i;
	int		nb_pipes;

	i = 0;
	nb_pipes = ft_lstsize(cmdlist->next);
	while (i < nb_pipes)
	{
		err_msg = get_next_line(shell->error_pipes[i][0]);
		close(shell->error_pipes[i][0]);
		if (err_msg)
		{
			ft_putstr_fd(err_msg, 2);
			free(err_msg);
		}
		i++;
	}
	return (0);
}

static int	fork_it_all(t_cmd *cmd, t_shell *shell,
							t_list *cmdlist, t_lexer **lexer)
{
	pid_t	pid;

	if (pipe(shell->pipe_fds) == -1)
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
		//CLOSE ALL ERROR PIPES NOT RELATED TO THIS CHILD
		if (write_and_read_pipe(cmdlist, cmd->nb, shell, cmd))
			free_all_exit(lexer, cmdlist, shell);
		executor(cmd, shell, cmdlist, lexer);
	}
	else if (pid == -1)
		return (fork_failure(shell->pipe_fds, shell->previous_pipe));
	transfer_pipes(cmd, shell, cmdlist, shell->pipe_fds);
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
	if (create_error_pipes(cmdlist, shell))
		return (0);
	while (iter)
	{
		cmd = iter->content;
		if (!fork_it_all(cmd, shell, cmdlist, lexer))
			return (0);
		iter = iter->next;
	}
	close_write_error_pipes(shell, cmdlist);
	read_error_messages(shell, cmdlist);
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
