/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pantoine <pantoine@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 22:05:54 by pantoine          #+#    #+#             */
/*   Updated: 2024/05/13 22:49:42 by pantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/evars.h"
#include "../../includes/execute.h"

static int	count_args_exit(t_cmd *cmd)
{
	int	len;

	len = 0;
	while (cmd->command[len])
		len++;
	return (len);
}

static int	exit_nonnumeric_arg(char *illegal_arg)
{
	ft_putstr_fd("exit\n", 1);
	ft_putstr_fd("petitcoq: exit: ", 2);
	ft_putstr_fd(illegal_arg, 2);
	ft_putstr_fd(": numeric argument required\n", 2);
	g_current_sig = 2;
	return (2);
}

static int	exit_too_many_args(int *status)
{
	ft_putstr_fd("exit\n", 1);
	ft_putstr_fd("petitcoq: exit: too many arguments\n", 2);
	g_current_sig = 1;
	*status = 1;
	return (1);
}

int	exit_petitcoq(t_cmd *cmd, int *status)
{
	int	i;
	int	len;

	i = 0;
	len = count_args_exit(cmd);
	while (cmd->command[1][i])
	{
		if (!ft_isdigit(cmd->command[1][i++]))
			return (exit_nonnumeric_arg(cmd->command[1]));
	}
	if (len > 2)
		return (exit_too_many_args(status));
	printf("exit\n");
	return (ft_atoi(cmd->command[1]));
}
