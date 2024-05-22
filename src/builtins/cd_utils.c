/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pantoine <pantoine@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 16:49:05 by pantoine          #+#    #+#             */
/*   Updated: 2024/05/22 11:19:16 by pantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/evars.h"
#include "../../includes/minishell.h"
#include "../../includes/execute.h"

int	change_pwd(t_shell *shell)
{
	char	*to_export;
	char	current[4096];
	t_evar	evar;

	if (!getcwd(current, 4096))
	{
		perror_context("getcwd", NULL);
		return (1);
	}
	to_export = ft_strjoin("PWD=", current);
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

int	change_oldpwd(t_shell *shell, char *old)
{
	char	*to_export;
	t_evar	evar;

	to_export = ft_strjoin("OLDPWD=", old);
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

int	cd_error_message(char *message)
{
	ft_putstr_fd("petitcoq: cd: ", 2);
	ft_putstr_fd(message, 2);
	ft_putstr_fd("\n", 2);
	g_current_sig = 1;
	return (-1);
}
