/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_dispatcher_utils.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pantoine <pantoine@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 18:18:12 by pantoine          #+#    #+#             */
/*   Updated: 2024/05/26 16:07:34 by pantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/evars.h"
#include "../../includes/execute.h"

int	dispatch_builtin(t_cmd *cmd, t_shell *shell)
{
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
	return (0);
}

int	is_same_str(char *s1, char *s2)
{
	if (ft_strlen(s1) != ft_strlen(s2))
		return (0);
	if (!ft_strncmp(s1, s2, ft_strlen(s1)))
		return (1);
	return (0);
}

int	reset_standard_in_out(int in, int out)
{
	if (dup2(in, STDIN_FILENO) == -1)
		perror_context("dup2", NULL);
	if (dup2(out, STDOUT_FILENO) == -1)
		perror_context("dup2", NULL);
	close(in);
	close(out);
	return (0);
}

int	save_standard_in_out(int *in, int *out)
{
	*in = dup(STDIN_FILENO);
	if (*in == -1)
	{
		perror_context("dup", NULL);
		return (1);
	}
	*out = dup(STDOUT_FILENO);
	if (*out == -1)
	{
		close(*in);
		perror_context("dup", NULL);
		return (1);
	}
	return (0);
}

int	fork_failure(int pipe_fds[2], int previous_pipe)
{
	close(pipe_fds[0]);
	close(pipe_fds[1]);
	perror_context("fork", NULL);
	if (previous_pipe != -2)
	{
		while (wait(NULL) != -1)
			;
		close(previous_pipe);
	}
	return (0);
}
