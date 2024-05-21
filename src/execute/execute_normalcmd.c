/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_normalcmd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pantoine <pantoine@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 18:57:58 by pantoine          #+#    #+#             */
/*   Updated: 2024/05/21 18:54:47 by pantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/evars.h"
#include "../../includes/execute.h"

static void	free_partial_envp_char(t_shell *shell, int i)
{
	int	j;

	j = 0;
	while (j < i)
		free(shell->envp_char[j++]);
	free(shell->envp_char);
}

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

int	reset_shlvl(t_shell *shell)
{
	char	*to_export;
	t_evar	evar;

	to_export = ft_strdup("SHLVL=1");
	if (!to_export)
	{
		perror_context("malloc", NULL);
		return (1);
	}
	if (init_change_evar(shell, &evar, to_export))
	{
		free(to_export);
		return (1);
	}
	return (0);
}

int	increase_shlvl(t_shell *shell)
{
	int		shlvl;
	char	*shlvl_value;
	char	*to_export;
	t_evar	evar;
	
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
	to_export = ft_strjoin("SHLVL=", shlvl_value);
	free(shlvl_value);
	if (!to_export)
	{
		perror_context("malloc", NULL);
		return (1);
	}
	if (init_change_evar(shell, &evar, to_export))
	{
		free(to_export);
		return (1);
	}
	free(to_export);
	return (0);
}

int	pimped_execve(t_cmd *cmd, t_shell *shell)
{

	if (dup_redirections(cmd))
	{
		g_current_sig = 1;
		return (1);
	}
	if (increase_shlvl(shell))
		return (1);	
	if (delist_envp(shell))
		return (1);
	if (!is_executable(cmd))
	{
		if (find_executable_path(cmd, shell))
			return (1);
	}
	if (execve(cmd->command[0], cmd->command, shell->envp_char) == -1)
	{
		perror_context("execve", cmd->command[0]);
		return (1);
	}
	return (0);
}

void	executor(t_cmd *cmd, t_shell *shell, t_list *cmdlist, t_lexer **lexer)
{
	if (!cmd->command[0])
		no_command(cmd);
	else if (is_builtin(cmd->command[0]))
		call_builtin(cmd, shell, cmdlist, lexer);
	else
	{
		pimped_execve(cmd, shell);
		if (errno == 2 && !g_current_sig)
			g_current_sig = 2;
		else if (errno == 13 && !g_current_sig)
			g_current_sig = 13;
	}
	free_all_exit(lexer, cmdlist, shell);
}
