/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_dispatcher.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pantoine <pantoine@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 16:34:22 by pantoine          #+#    #+#             */
/*   Updated: 2024/05/15 17:03:56 by pantoine         ###   ########.fr       */
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

int	call_builtin(t_cmd *cmd, t_shell *shell, t_list *cmdlist, t_lexer **lexer)
{
	int			saved;

	saved = dup(1);
	dup_redirections(cmd);
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

int	executor(t_cmd *cmd, t_shell *shell)
{
	(void)cmd;
	(void)shell;
	printf("real command, not fake\n");
	return (1);
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

int	dispatch_commands(t_list *cmdlist, t_shell *shell, t_lexer **lexer)
{
	t_list	*iter;
	t_cmd	*cmd;

	iter = cmdlist->next;
	while (iter)
	{
		cmd = iter->content;
		if (!cmd->command[0])
			no_command(cmd);
		else if (is_builtin(cmd->command[0]))
			call_builtin(cmd, shell, cmdlist, lexer);
		else
			executor(cmd, shell);
		iter = iter->next;
	}
	/*
	while (wait(NULL) != -1)
		;*/
	return (1);
}
