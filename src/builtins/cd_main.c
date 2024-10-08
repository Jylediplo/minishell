/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pantoine <pantoine@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 15:12:42 by pantoine          #+#    #+#             */
/*   Updated: 2024/06/02 16:45:16 by pantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/execute.h"
#include "../../includes/evars.h"

static int	count_args_cd(t_cmd *cmd)
{
	int		len;

	len = 0;
	while (cmd->command[len])
		len++;
	if (len > 2)
		return (cd_error_message("too many arguments", cmd->error_pipe[1]));
	return (len);
}

static int	get_chdir_status(int len, t_cmd *cmd, t_list **envp)
{
	char	*home;

	if (len == -1)
		return (1);
	else if (len == 1)
	{
		home = get_envvar_value(envp, "HOME");
		if (!home)
			return (cd_error_message("HOME not set", cmd->error_pipe[1]));
		if (chdir(get_envvar_value(envp, "HOME")) == -1)
		{
			perror_context("cd", NULL, cmd->error_pipe[1]);
			g_current_sig = 1;
			return (1);
		}
	}
	else if (chdir(cmd->command[1]) == -1)
	{
		perror_context("cd", cmd->command[1], cmd->error_pipe[1]);
		g_current_sig = 1;
		return (1);
	}
	return (0);
}

static int	changedir_validcurrent(t_shell *shell, t_cmd *cmd,
										char old[4096], int len)
{
	if (len == -1)
		return (1);
	if (change_oldpwd(shell, old, cmd, 1))
		return (1);
	if (get_chdir_status(len, cmd, &shell->envp))
		return (1);
	if (change_pwd(shell, cmd->error_pipe[1], cmd))
		return (1);
	return (0);
}

static int	changedir_parenterror(t_shell *shell, t_cmd *cmd, char old[4096])
{
	ft_putstr_fd("petitcoq: error retrieving current/parent directories\n",
		cmd->error_pipe[1]);
	if (change_oldpwd(shell, old, cmd, 0))
		return (1);
	if (change_pwd(shell, cmd->error_pipe[1], cmd))
		return (1);
	return (0);
}

int	change_directory(t_cmd *cmd, t_shell *shell)
{
	char	old[4096];
	int		len;
	int		already_changed;

	already_changed = 0;
	len = count_args_cd(cmd);
	if (!getcwd(old, 4096) && errno == ENOENT)
	{
		if (get_chdir_status(len, cmd, &shell->envp))
			return (1);
		already_changed = 1;
	}
	if (!getcwd(old, 4096) && errno == ENOENT)
		return (changedir_parenterror(shell, cmd, old));
	if (!already_changed)
		return (changedir_validcurrent(shell, cmd, old, len));
	else
	{
		if (change_oldpwd(shell, old, cmd, 0))
			return (1);
		if (change_pwd(shell, cmd->error_pipe[1], cmd))
			return (1);
	}
	return (0);
}
