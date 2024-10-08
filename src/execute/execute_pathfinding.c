/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pathfinding.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pantoine <pantoine@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 18:10:14 by pantoine          #+#    #+#             */
/*   Updated: 2024/05/28 16:52:29 by pantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/evars.h"
#include "../../includes/execute.h"

static int	is_a_dir(t_cmd *cmd)
{
	struct stat	stats;

	stats.st_mode = 0;
	if (stat(cmd->command[0], &stats) == -1)
	{
		perror_context("stat", NULL, cmd->error_pipe[1]);
		return (0);
	}
	if (S_ISDIR(stats.st_mode))
		return (1);
	return (0);
}

int	is_executable(t_cmd *cmd)
{
	if (!access(cmd->command[0], F_OK | X_OK))
	{
		if (is_a_dir(cmd))
		{
			is_a_dir_error(cmd);
			return (2);
		}
		return (1);
	}
	return (0);
}

static int	search_and_match_path(char **paths, t_cmd *cmd)
{
	int		i;
	char	*temp;
	char	*exec_file;

	i = 0;
	while (paths[i])
	{
		temp = ft_strjoin(paths[i++], "/");
		if (!temp)
			return (1);
		exec_file = ft_strjoin(temp, cmd->command[0]);
		if (!exec_file)
			return (free(temp), 1);
		if (!access(exec_file, F_OK))
		{
			free(temp);
			free(cmd->command[0]);
			cmd->command[0] = exec_file;
			return (0);
		}
		free(temp);
		free(exec_file);
	}
	return (0);
}

void	free_split(char **tofree)
{
	int	i;

	i = 0;
	while (tofree[i])
		free(tofree[i++]);
	free(tofree);
}

int	find_executable_path(t_cmd *cmd, t_shell *shell)
{
	char	**paths;
	char	*path_value;

	if (ft_strchr(cmd->command[0], '/'))
		return (0);
	path_value = get_envvar_value(&shell->envp, "PATH");
	if (!path_value)
		return (0);
	paths = ft_split(path_value, ':');
	if (!paths)
	{
		perror_context("malloc", NULL, cmd->error_pipe[1]);
		return (1);
	}
	if (search_and_match_path(paths, cmd))
	{
		free_split(paths);
		perror_context("malloc", NULL, cmd->error_pipe[1]);
		return (1);
	}
	free_split(paths);
	return (0);
}
