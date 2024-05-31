/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_onecommand.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pantoine <pantoine@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 18:01:15 by pantoine          #+#    #+#             */
/*   Updated: 2024/05/31 17:38:38 by pantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/evars.h"
#include "../../includes/execute.h"

static int	wait_update_exitsig(void)
{
	int		status;

	waitpid(-1, &status, 0);
	update_current_sig(&status);
	return (0);
}

void	handler_fork(int sig)
{
	g_current_sig = 128 + sig;
	if (sig == SIGQUIT)
	{
		printf("Quit (core dumped)\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		exit(g_current_sig);
	}
}

static int	fork_one_command(t_cmd *cmd, t_shell *shell,
								t_list *cmdlist, t_lexer **lexer)
{
	handle_signals(SIG_EXEC);
	shell->children[cmd->nb - 1].childprocess_pid = fork();
	if (!shell->children[cmd->nb - 1].childprocess_pid)
	{
		close(cmd->error_pipe[0]);
		pimped_execve(cmd, shell);
		close(cmd->error_pipe[1]);
		free_all_exit(lexer, cmdlist, shell, 1);
		return (1);
	}
	else if (shell->children[cmd->nb - 1].childprocess_pid == -1)
	{
		perror_context("fork", NULL, 2);
		return (1);
	}
	ignore_sigint();
	wait_update_exitsig();
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
	cmd->error_pipe = shell->children[cmd->nb - 1].error_pipe;
	if (!cmd->command[0])
	{
		no_command(cmd);
		close_pipe(cmd->error_pipe);
		return (1);
	}
	else if (is_builtin(cmd->command[0]))
		call_builtin(cmd, shell, cmdlist, lexer);
	else
		fork_one_command(cmd, shell, cmdlist, lexer);
	close_write_error_pipes(shell, cmdlist);
	read_error_messages(shell,
		shell->children[cmd->nb - 1].childprocess_pid, 0);
	return (1);
}
