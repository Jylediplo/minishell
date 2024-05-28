/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_error_pipes_utils.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pantoine <pantoine@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 18:40:26 by pantoine          #+#    #+#             */
/*   Updated: 2024/05/28 18:43:38 by pantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/evars.h"
#include "../../includes/execute.h"

void	free_error_pipes(t_shell *shell, t_list *cmdlist)
{
	t_list	*iter;
	int		i;

	i = 0;
	iter = cmdlist->next;
	while (iter)
	{
		free(shell->error_pipes[i++]);
		iter = iter->next;
	}
	free(shell->error_pipes);
}
