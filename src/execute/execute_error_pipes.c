/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_error_pipes.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pantoine <pantoine@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 17:04:46 by pantoine          #+#    #+#             */
/*   Updated: 2024/05/28 19:59:31 by pantoine         ###   ########.fr       */
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
			close_pipe(shell->error_pipes[i]);
		i++;
	}
}

void	free_close_partial_pipe_array(t_shell *shell, int i)
{
	int	j;

	j = 0;
	while (j < i)
	{
		close_pipe(shell->error_pipes[j]);
		free(shell->error_pipes[j++]);
	}
	free(shell->error_pipes);
	shell->error_pipes = NULL;
}

int	create_error_pipes(t_list *cmdlist, t_shell *shell)
{
	t_list	*iter;
	int		i;
	int		j;

	iter = cmdlist->next;
	i = 0;
	j = 2;
	shell->error_pipes = malloc(sizeof(int *) * ft_lstsize(iter));
	if (!shell->error_pipes)
	{
		perror_context("malloc", NULL, 2);
		return (0);
	}
	while (iter)
	{
		if (i != j)
			shell->error_pipes[i] = malloc(sizeof(int) * 2);
		else
			shell->error_pipes[i] = NULL;
		if (!shell->error_pipes[i])
		{
			free_close_partial_pipe_array(shell, i);
			perror_context("malloc", NULL, 2);
			return (1);
		}
		if (pipe(shell->error_pipes[i]) == -1)
		{
			free_close_partial_pipe_array(shell, i);
			perror_context("pipe", NULL, 2);
			return (1);
		}
		i++;
		iter = iter->next;
	}
	return (0);
}

int	read_error_messages(t_shell *shell, t_list *cmdlist)
{
	char	*err_msg;
	int		i;
	int		nb_pipes;

	i = 0;
	nb_pipes = ft_lstsize(cmdlist->next);
	while (i < nb_pipes)
	{
		while (1)
		{
			err_msg = get_next_line(shell->error_pipes[i][0]);
			if (err_msg)
			{
				ft_putstr_fd(err_msg, 2);
				free(err_msg);
			}
			else
			{
				close(shell->error_pipes[i][0]);
				break ;
			}
		}
		i++;
	}
	return (0);
}

void	close_write_error_pipes(t_shell *shell, t_list *cmdlist)
{
	int	i;

	i = ft_lstsize(cmdlist->next) - 1;
	while (i >= 0)
		close(shell->error_pipes[i--][1]);
}
