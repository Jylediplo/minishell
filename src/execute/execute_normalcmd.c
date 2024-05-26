/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_normalcmd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pantoine <pantoine@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 18:57:58 by pantoine          #+#    #+#             */
/*   Updated: 2024/05/26 14:04:50 by pantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/evars.h"
#include "../../includes/execute.h"

static int	delist_envp(t_shell *shell)
{
	t_list	*iter;
	int		i;

	i = 0;
	shell->envp_char = malloc(sizeof(char *) * (ft_lstsize(shell->envp) + 1));
	if (!shell->envp_char)
	{
		perror_context("malloc", NULL);
		return (1);
	}
	iter = shell->envp;
	while (iter)
	{
		shell->envp_char[i] = ft_strdup(iter->content);
		if (!shell->envp_char[i])
		{
			perror_context("malloc", NULL);
			free_partial_envp_char(shell, i);
			return (1);
		}
		i++;
		iter = iter->next;
	}
	shell->envp_char[i] = NULL;
	return (0);
}

static int	increase_shlvl(t_shell *shell)
{
	int		shlvl;
	char	*shlvl_value;

	shlvl_value = get_envvar_value(&shell->envp, "SHLVL");
	if (!shlvl_value || !shlvl_value[0])
		return (reset_shlvl(shell));
	shlvl = ft_atoi(shlvl_value);
	shlvl_value = ft_itoa(++shlvl);
	if (!shlvl_value)
	{
		perror_context("malloc", NULL);
		return (1);
	}
	if (export_newshlvl(shell, shlvl_value))
		return (1);
	return (0);
}

static int	replace_with_executable(t_cmd *cmd, t_shell *shell)
{
	if (!is_executable(cmd) && !is_a_dir(cmd))
	{
		if (find_executable_path(cmd, shell))
		{
			free_split(shell->envp_char);
			return (1);
		}
	}
	else if (is_a_dir(cmd))
	{
		free_split(shell->envp_char);
		is_a_dir_error(cmd);
		return (1);
	}
	return (0);
}

int	pimped_execve(t_cmd *cmd, t_shell *shell)
{
	if (dup_redirections(cmd))
		return (1);
	if (increase_shlvl(shell))
		return (1);
	if (delist_envp(shell))
		return (1);
	if (replace_with_executable(cmd, shell))
		return (1);
	if (execve(cmd->command[0], cmd->command, shell->envp_char) == -1)
	{
		perror_context("execve", cmd->command[0]);
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
	free_all_exit(lexer, cmdlist, shell);
}
