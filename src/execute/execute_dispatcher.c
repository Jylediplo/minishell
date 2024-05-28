/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_dispatcher.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lefabreg <lefabreg@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 16:34:22 by pantoine          #+#    #+#             */
/*   Updated: 2024/05/16 19:16:36 by lefabreg         ###   ########lyon.fr   */
/*   Updated: 2024/05/16 18:24:53 by pantoine         ###   ########.fr       */
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
	int			saved;

	saved = dup(1);
	dup_redirections(cmd);
	dup2(saved, 1);
	close(saved);
	return (0);
}

int	call_builtin(t_cmd *cmd, t_shell *shell, t_list *cmdlist, t_lexer **lexer)
{
	int			saved;

	saved = dup(1);
	if (dup_redirections(cmd))
	{
		close(saved);
		return (1);
	}
	if (is_same_str(cmd->command[0], "echo"))
		efftee_echo(cmd->command);
	else if (is_same_str(cmd->command[0], "cd"))
		change_directory(cmd, shell);
	else if (is_same_str(cmd->command[0], "pwd"))
		get_pwd();
	else if (is_same_str(cmd->command[0], "export"))
		export_envar(cmd, shell);
	else if (is_same_str(cmd->command[0], "unset"))
		unset_envvar(cmd, shell);
	else if (is_same_str(cmd->command[0], "env"))
		show_me_the_way(shell->envp);
	else if (is_same_str(cmd->command[0], "exit"))
      {
                close(saved);
        		exit_petitcoq(cmd, cmdlist, lexer, shell);
		}
	dup2(saved, 1);
	close(saved);
	return (0);
}

int	fork_it_all(t_cmd *cmd, t_shell *shell, t_list *cmdlist, t_lexer **lexer)
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
		fork_it_all(cmd, shell, cmdlist, lexer);
		iter = iter->next;
	}
	while (waitpid(-1, &status, 0) != -1)
		;
	g_current_sig = status;
	return (1);
}
