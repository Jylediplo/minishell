/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_normalcmd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pantoine <pantoine@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 18:57:58 by pantoine          #+#    #+#             */
/*   Updated: 2024/05/17 11:15:09 by pantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/evars.h"
#include "../../includes/execute.h"

int	pimped_execve(t_cmd *cmd, t_shell *shell)
{
	char	**path;

	//path = ft_split(get_envvar_value(&shell->envp, "PATH"), ':');
	(void)shell;
	(void)path;
	if (dup_redirections(cmd))
		return (1);
	if (execve(cmd->command[0], cmd->command, NULL) == -1)
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
		pimped_execve(cmd, shell);
	free_all_exit(lexer, cmdlist, shell);
}
