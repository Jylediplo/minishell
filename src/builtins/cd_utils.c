/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pantoine <pantoine@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 16:49:05 by pantoine          #+#    #+#             */
/*   Updated: 2024/05/31 19:09:27 by pantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/evars.h"
#include "../../includes/minishell.h"
#include "../../includes/execute.h"

static int	is_currently_valid(char current[4096], int fd)
{
	int	res;

	res = 1;
	if (!getcwd(current, 4096))
	{
		res = 0;
		perror_context("getcwd", NULL, fd);
	}
	return (res);
}

int	change_pwd(t_shell *shell, int fd, t_cmd *cmd)
{
	char	*to_export;
	char	current[4096];
	t_evar	evar;
	int		valid_current;

	valid_current = is_currently_valid(current, cmd->error_pipe[1]);
	if (valid_current)
		to_export = ft_strjoin("PWD=", current);
	else
		to_export = ft_strjoin("PWD+=", cmd->command[1]);
	if (!to_export)
	{
		perror_context("malloc", NULL, fd);
		return (1);
	}
	if (init_change_evar(shell, &evar, to_export, fd))
	{
		free(to_export);
		return (1);
	}
	free(to_export);
	return (0);
}

int	change_oldpwd(t_shell *shell, char *old, t_cmd *cmd, int valid_current)
{
	char	*to_export;
	t_evar	evar;

	if (!valid_current)
		to_export = ft_strjoin("OLPWD=", get_envvar_value(&shell->envp, "PWD"));
	else
		to_export = ft_strjoin("OLDPWD=", old);
	if (!to_export)
	{
		perror_context("malloc", NULL, cmd->error_pipe[1]);
		return (1);
	}
	if (init_change_evar(shell, &evar, to_export, cmd->error_pipe[1]))
	{
		free(to_export);
		return (1);
	}
	free(to_export);
	return (0);
}

int	cd_error_message(char *message, int fd)
{
	ft_putstr_fd("petitcoq: cd: ", fd);
	ft_putstr_fd(message, fd);
	ft_putstr_fd("\n", fd);
	g_current_sig = 1;
	return (-1);
}
