/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_normalcmd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pantoine <pantoine@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 18:57:58 by pantoine          #+#    #+#             */
/*   Updated: 2024/05/28 19:44:59 by pantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/evars.h"
#include "../../includes/execute.h"

static int	delist_envp(t_shell *shell, int fd)
{
	t_list	*iter;
	int		i;

	i = 0;
	shell->envp_char = malloc(sizeof(char *) * (ft_lstsize(shell->envp) + 1));
	if (!shell->envp_char)
	{
		perror_context("malloc", NULL, fd);
		return (1);
	}
	iter = shell->envp;
	while (iter)
	{
		shell->envp_char[i] = ft_strdup(iter->content);
		if (!shell->envp_char[i])
		{
			perror_context("malloc", NULL, fd);
			free_partial_envp_char(shell, i);
			return (1);
		}
		i++;
		iter = iter->next;
	}
	shell->envp_char[i] = NULL;
	return (0);
}

static int	increase_shlvl(t_shell *shell, int fd)
{
	int		shlvl;
	char	*shlvl_value;

	shlvl_value = get_envvar_value(&shell->envp, "SHLVL");
	if (!shlvl_value || !shlvl_value[0])
		return (reset_shlvl(shell, fd));
	shlvl = ft_atoi(shlvl_value);
	shlvl_value = ft_itoa(++shlvl);
	if (!shlvl_value)
	{
		perror_context("malloc", NULL, fd);
		return (1);
	}
	if (export_newshlvl(shell, shlvl_value, fd))
		return (1);
	return (0);
}

static int	replace_with_executable(t_cmd *cmd, t_shell *shell)
{
	int	status;

	status = is_executable(cmd);
	if (!status)
	{
		if (find_executable_path(cmd, shell))
		{
			free_split(shell->envp_char);
			return (1);
		}
	}
	else if (status == 2)
	{
		free_split(shell->envp_char);
		return (1);
	}
	return (0);
}

int	pimped_execve(t_cmd *cmd, t_shell *shell)
{
	if (dup_redirections(cmd))
		return (1);
	if (increase_shlvl(shell, cmd->error_pipe[1]))
		return (1);
	if (delist_envp(shell, cmd->error_pipe[1]))
		return (1);
	if (replace_with_executable(cmd, shell))
		return (1);
	//close(cmd->error_pipe[1]); if we close, no execve error reported but no open fd...
	if (execve(cmd->command[0], cmd->command, shell->envp_char) == -1)
	{
		perror_context("execve", cmd->command[0], cmd->error_pipe[1]);
		free_split(shell->envp_char);
		return (1);
	}
	return (0);
}

void	executor(t_cmd *cmd, t_shell *shell,
					t_list *cmdlist, t_lexer **lexer)
{
	if (!cmd->command[0])
		no_command(cmd);
	else if (is_builtin(cmd->command[0]))
		call_builtin(cmd, shell, cmdlist, lexer);
	else
		pimped_execve(cmd, shell);
	close(cmd->error_pipe[1]);
	free_all_exit(lexer, cmdlist, shell);
}
