/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_normalcmd_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pantoine <pantoine@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 12:28:50 by pantoine          #+#    #+#             */
/*   Updated: 2024/05/28 16:51:00 by pantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/evars.h"
#include "../../includes/execute.h"

int	is_a_dir_error(t_cmd *cmd)
{
	ft_putstr_fd("petitcoq: ", 2);
	ft_putstr_fd(cmd->command[0], 2);
	ft_putstr_fd(": Is a directory\n", 2);
	g_current_sig = 13;
	return (1);
}

void	free_partial_envp_char(t_shell *shell, int i)
{
	int	j;

	j = 0;
	while (j < i)
		free(shell->envp_char[j++]);
	free(shell->envp_char);
}

int	reset_shlvl(t_shell *shell, int fd)
{
	char	*to_export;
	t_evar	evar;

	to_export = ft_strdup("SHLVL=1");
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

int	export_newshlvl(t_shell *shell, char *shlvl_value, int fd)
{
	char	*to_export;
	t_evar	evar;

	to_export = ft_strjoin("SHLVL=", shlvl_value);
	free(shlvl_value);
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
