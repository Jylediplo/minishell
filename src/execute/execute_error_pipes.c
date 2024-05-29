/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_error_pipes.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pantoine <pantoine@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 17:04:46 by pantoine          #+#    #+#             */
/*   Updated: 2024/05/29 12:28:39 by pantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/evars.h"
#include "../../includes/execute.h"

void	close_pipe(int pipe[2])
{
	close(pipe[0]);
	close(pipe[1]);
}

void	close_unused_error_pipes(t_shell *shell, t_list *cmdlist, int nb_cmd)
{
	int	i;
	int	nb_pipes;

	i = 0;
	nb_pipes = ft_lstsize(cmdlist->next);
	while (i < nb_pipes)
	{
		if (i != nb_cmd - 1)
			close_pipe(shell->children[i].error_pipe);
		i++;
	}
}

int	create_error_pipes(t_list *cmdlist, t_shell *shell)
{
	t_list	*iter;
	int		i;

	iter = cmdlist->next;
	i = 0;
	shell->children = malloc(sizeof(t_childprocess) * ft_lstsize(iter));
	if (!shell->children)
	{
		perror_context("malloc", NULL, 2);
		return (0);
	}
	while (iter)
	{
		if (open_error_pipes(shell, i))
			return (1);
		shell->children[i].childprocess_pid = -2;
		i++;
		iter = iter->next;
	}
	return (0);
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

void	close_write_error_pipes(t_shell *shell, t_list *cmdlist)
{
	int	i;

	i = ft_lstsize(cmdlist->next) - 1;
	while (i >= 0)
		close(shell->children[i--].error_pipe[1]);
}
