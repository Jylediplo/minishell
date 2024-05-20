/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_dispatcher.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lefabreg <lefabreg@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 16:34:22 by pantoine          #+#    #+#             */
/*   Updated: 2024/05/20 23:14:19 by pantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/evars.h"
#include "../../includes/execute.h"

int	is_same_str(char *s1, char *s2)
{
	if (ft_strlen(s1) != ft_strlen(s2))
		return (0);
	if (!ft_strncmp(s1, s2, ft_strlen(s1)))
		return (1);
	return (0);
}

int	no_command(t_cmd *cmd)
{
	int		saved_in;
	int		saved_out;

	saved_in = dup(STDIN_FILENO);
	saved_out = dup(STDOUT_FILENO);
	if (dup_redirections(cmd))
	{
		close(saved_in);
		close(saved_out);
	}
	dup2(saved_in, STDIN_FILENO);
	dup2(saved_out, STDOUT_FILENO);
	close(saved_in);
	close(saved_out);
	return (0);
}

int	call_builtin(t_cmd *cmd, t_shell *shell, t_list *cmdlist, t_lexer **lexer)
{
	int		saved_out;
	int		saved_in;

	saved_in = dup(STDIN_FILENO);
	saved_out = dup(STDOUT_FILENO);
	if (dup_redirections(cmd))
	{
		close(saved_in);
		close(saved_out);
		return (1);
	}
	if (is_same_str(cmd->command[0], "exit"))
    {
		close(saved_in);
		close(saved_out);
		exit_petitcoq(cmd, cmdlist, lexer, shell);
	}
	else
		dispatch_builtin(cmd, shell);
	dup2(saved_in, STDIN_FILENO);
	dup2(saved_out, STDOUT_FILENO);
	close(saved_in);
	close(saved_out);
	return (0);
}

static int	fork_it_all(t_cmd *cmd, t_shell *shell, t_list *cmdlist, t_lexer **lexer)
{
	pid_t		pid;
	int			pipe_fds[2];

	if (pipe(pipe_fds) == -1)
	{
		perror_context("pipe", NULL);
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
	{
		close(pipe_fds[0]);
		close(pipe_fds[1]);
		perror_context("fork", NULL);
		return (0);
	}
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
	while (iter)
	{
		cmd = iter->content;
		if (!fork_it_all(cmd, shell, cmdlist, lexer))
			return (0);
		iter = iter->next;
	}
	while (waitpid(-1, &status, 0) != -1)
		;
	if (WEXITSTATUS(status) == 2)
		g_current_sig = 125 + WEXITSTATUS(status);
	return (1);
}
