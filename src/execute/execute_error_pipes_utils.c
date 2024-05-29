/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_error_pipes_utils.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pantoine <pantoine@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 18:40:26 by pantoine          #+#    #+#             */
/*   Updated: 2024/05/29 15:59:11 by pantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/evars.h"
#include "../../includes/execute.h"

static void	free_close_partial_pipe_array(t_shell *shell, int i)
{
	int	j;

	j = 0;
	while (j < i)
		close_pipe(shell->children[j++].error_pipe);
	free(shell->children);
	shell->children = NULL;
}

int	open_error_pipes(t_shell *shell, int i)
{
	if (pipe(shell->children[i].error_pipe) == -1)
	{
		free_close_partial_pipe_array(shell, i);
		perror_context("pipe", NULL, 2);
		return (1);
	}
	return (0);
}
