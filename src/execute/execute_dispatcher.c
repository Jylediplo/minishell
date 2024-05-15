/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_dispatcher.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pantoine <pantoine@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 16:34:22 by pantoine          #+#    #+#             */
/*   Updated: 2024/05/15 19:30:53 by pantoine         ###   ########.fr       */
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
		exit_petitcoq(cmd, cmdlist, lexer, shell);
	dup2(saved, 1);
	close(saved);
	return (0);
}

int	fork_it_all(t_cmd *cmd, t_shell *shell, t_list *cmdlist, t_lexer **lexer)
{
	pid_t	pid;
	int		pipe_fds[2];

	if (pipe(pipe_fds) == -1)
		return (0);
	pid = fork();
	if (!pid)
	{
		if (dup2(pipe_fds[0], 0) == -1)
			printf("couldnt use the pipe!\n");
		if (dup2(pipe_fds[1], 1) == -1)
			printf("couldnt use the pipe!\n");
		if (!cmd->command[0])
			no_command(cmd);
		else if (is_builtin(cmd->command[0]))
			call_builtin(cmd, shell, cmdlist, lexer);
		else
			pimped_execve(cmd, shell);
		exit(g_current_sig);
	}
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
