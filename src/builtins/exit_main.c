/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pantoine <pantoine@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 22:05:54 by pantoine          #+#    #+#             */
/*   Updated: 2024/05/29 12:31:28 by pantoine         ###   ########.fr       */
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

static int	exit_nonnumeric_arg(t_cmd *cmd, t_list *cmdlist,
						t_lexer **lexer, t_shell *shell)
{
	ft_putstr_fd("exit\n", cmd->error_pipe[1]);
	ft_putstr_fd("petitcoq: exit: ", cmd->error_pipe[1]);
	ft_putstr_fd(cmd->command[1], cmd->error_pipe[1]);
	ft_putstr_fd(": numeric argument required\n", cmd->error_pipe[1]);
	close(cmd->error_pipe[1]);
	/*
	if (ft_lstsize(cmdlist->next))
		read_error_messages(shell, cmdlist);*/
	g_current_sig = 255;
	free_all_exit(lexer, cmdlist, shell);
	return (2);
}

static int	exit_too_many_args(int fd)
{
	ft_putstr_fd("exit\n", fd);
	ft_putstr_fd("petitcoq: exit: too many arguments\n", fd);
	g_current_sig = 1;
	return (1);
}

void	free_all_exit(t_lexer **lexer, t_list *cmdlist, t_shell *shell)
{
	free_error_pipes(shell);
	free_lexer(lexer);
	free_command_arrays(cmdlist);
	free_cmdlist(cmdlist);
	free_envp(shell->envp);
	exit(g_current_sig);
}

int	exit_petitcoq(t_cmd *cmd, t_list *cmdlist, t_lexer **lexer, t_shell *shell)
{
	int				i;
	int				len;

	i = 0;
	len = count_args_exit(cmd);
	if (len == 1)
	{
		g_current_sig = 0;
		close(cmd->error_pipe[1]);
		if (ft_lstsize(cmdlist->next) == 1)
		{
			printf("exit\n");
			close(cmd->error_pipe[0]);
		}
		free_all_exit(lexer, cmdlist, shell);
	}
	if (cmd->command[1][0] == '-')
		i++;
	while (cmd->command[1][i])
	{
		if (!ft_isdigit(cmd->command[1][i++]))
			exit_nonnumeric_arg(cmd, cmdlist, lexer, shell);
	}
	if (len > 2)
		return (exit_too_many_args(cmd->error_pipe[1]));
	g_current_sig = (unsigned char)ft_atoi(cmd->command[1]);
	printf("exit\n");
	close(cmd->error_pipe[1]);
	if (ft_lstsize(cmdlist->next) == 1)
		close(cmd->error_pipe[0]);
	free_all_exit(lexer, cmdlist, shell);
	return (0);
}
