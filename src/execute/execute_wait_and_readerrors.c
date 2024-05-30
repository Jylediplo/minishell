/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_wait_and_readerrors.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pantoine <pantoine@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 16:12:16 by pantoine          #+#    #+#             */
/*   Updated: 2024/05/29 16:16:15 by pantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/execute.h"

void	update_current_sig(int status)
{
	if (WIFEXITED(status) && WEXITSTATUS(status) == 2)
		g_current_sig = 127;
	else if (WIFEXITED(status) && WEXITSTATUS(status) == 13)
		g_current_sig = 126;
	else
		g_current_sig = WEXITSTATUS(status);
}

void	wait_for_children(t_shell *shell, t_list *cmdlist)
{
	int		status;
	pid_t	pid;
	int		remaining_children;
	int		nb_cmd;
	int		i;

	i = 0;
	nb_cmd = ft_lstsize(cmdlist->next);
	remaining_children = nb_cmd;
	while (remaining_children > 0)
	{
		pid = waitpid(-1, &status, 0);
		if (pid == -1)
			break ;
		while (i < nb_cmd)
		{
			read_error_messages(shell, pid, i);
			i++;
		}
		i = 0;
		remaining_children--;
	}
	update_current_sig(status);
}

int	read_error_messages(t_shell *shell, pid_t pid, int i)
{
	char	*err_msg;

	if (pid == shell->children[i].childprocess_pid)
	{
		while (1)
		{
			err_msg = get_next_line(shell->children[i].error_pipe[0]);
			if (err_msg)
			{
				ft_putstr_fd(err_msg, 2);
				free(err_msg);
			}
			else
			{
				close(shell->children[i].error_pipe[0]);
				break ;
			}
		}
	}
	return (0);
}
