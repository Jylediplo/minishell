/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pantoine <pantoine@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 11:02:40 by pantoine          #+#    #+#             */
/*   Updated: 2024/05/31 11:04:53 by pantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/evars.h"
#include "../../includes/execute.h"

int	count_args_exit(t_cmd *cmd)
{
	int	len;

	len = 0;
	while (cmd->command[len])
		len++;
	return (len);
}

void	exit_single_arg(t_shell *shell, t_lexer **lexer,
			t_list *cmdlist, t_cmd *cmd)
{
	g_current_sig = (unsigned char)ft_atoi(cmd->command[1]);
	printf("exit\n");
	close(cmd->error_pipe[1]);
	if (ft_lstsize(cmdlist->next) == 1)
	{
		close(cmd->error_pipe[0]);
		free_all_exit(lexer, cmdlist, shell, 0);
	}
	else
		free_all_exit(lexer, cmdlist, shell, 1);
}

void	exit_no_arg(t_shell *shell, t_lexer **lexer,
			t_list *cmdlist, t_cmd *cmd)
{
	g_current_sig = 0;
	close(cmd->error_pipe[1]);
	if (ft_lstsize(cmdlist->next) == 1)
	{
		printf("exit\n");
		close(cmd->error_pipe[0]);
		free_all_exit(lexer, cmdlist, shell, 0);
	}
	free_all_exit(lexer, cmdlist, shell, 1);
}
