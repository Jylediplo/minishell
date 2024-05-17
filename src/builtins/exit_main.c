/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pantoine <pantoine@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 22:05:54 by pantoine          #+#    #+#             */
/*   Updated: 2024/05/17 11:37:45 by pantoine         ###   ########.fr       */
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

static int	exit_nonnumeric_arg(char *illegal_arg, t_list *cmdlist,
						t_lexer **lexer, t_shell *shell)
{
	ft_putstr_fd("exit\n", 1);
	ft_putstr_fd("petitcoq: exit: ", 2);
	ft_putstr_fd(illegal_arg, 2);
	ft_putstr_fd(": numeric argument required\n", 2);
	g_current_sig = 2;
	free_lexer(lexer);
	free_command_arrays(cmdlist);
	free_cmdlist(cmdlist);
	free_envp(shell->envp);
	exit(g_current_sig);
	return (2);
}

static int	exit_too_many_args(void)
{
	ft_putstr_fd("exit\n", 1);
	ft_putstr_fd("petitcoq: exit: too many arguments\n", 2);
	g_current_sig = 1;
	return (1);
}

void	free_all_exit(t_lexer **lexer, t_list *cmdlist, t_shell *shell)
{
	free_lexer(lexer);
	free_command_arrays(cmdlist);
	free_cmdlist(cmdlist);
	free_envp(shell->envp);
	exit(g_current_sig);
}

int	exit_petitcoq(t_cmd *cmd, t_list *cmdlist, t_lexer **lexer, t_shell *shell)
{
	int		i;
	int		len;
	char	value;

	i = 0;
	len = count_args_exit(cmd);
	if (len == 1)
	{
		printf("exit\n");
		free_all_exit(lexer, cmdlist, shell);
	}
	if (cmd->command[1][0] == '-')
		i++;
	value = (unsigned char)ft_atoi(cmd->command[1]);
	while (cmd->command[1][i])
	{
		if (!ft_isdigit(cmd->command[1][i++]))
			exit_nonnumeric_arg(cmd->command[1], cmdlist, lexer, shell);
	}
	if (len > 2)
		return (exit_too_many_args());
	g_current_sig = value;
	printf("exit\n");
	free_all_exit(lexer, cmdlist, shell);
	return (0);
}
