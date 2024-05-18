/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_normalcmd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pantoine <pantoine@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 18:57:58 by pantoine          #+#    #+#             */
/*   Updated: 2024/05/18 11:37:14 by pantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/evars.h"
#include "../../includes/execute.h"

void	free_partial_envp_char(t_shell *shell, int i)
{
	int	j;

	j = 0;
	while (j < i)
		free(shell->envp_char[j++]);
	free(shell->envp_char);
}

int	delist_envp(t_shell *shell)
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

int	is_executable(t_cmd *cmd)
{
	if (!access(cmd->command[0], F_OK))
		return (1);
	return (0);
}

int	find_executable_path(t_cmd *cmd, t_shell *shell)
{
	int		i;
	char	*exec_file;
	char	*temp;
	char	**paths;
	char	*path_value;
	
	i = 0;
	path_value = get_envvar_value(&shell->envp, "PATH");
	if (!path_value)
		return (0);
	paths = ft_split(path_value, ':');
	if (!paths)
		return (0);
	while (paths[i])
	{
		temp = ft_strjoin(paths[i], "/");
		exec_file = ft_strjoin(temp, cmd->command[0]);
		if (!access(exec_file, F_OK))
		{
			free(temp);
			free(cmd->command[0]);
			cmd->command[0] = exec_file;
			break ;
		}
		free(temp);
		free(exec_file);
		i++;
	}
	return (0);
}

int	pimped_execve(t_cmd *cmd, t_shell *shell)
{

	if (dup_redirections(cmd))
		return (1);
	if (delist_envp(shell))
		return (1);
	if (!is_executable(cmd))
		find_executable_path(cmd, shell);
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
		pimped_execve(cmd, shell);
	free_all_exit(lexer, cmdlist, shell);
}
