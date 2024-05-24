/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_transform_cmdlist.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pantoine <pantoine@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 23:39:10 by pantoine          #+#    #+#             */
/*   Updated: 2024/05/24 14:03:22 by pantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execute.h"
#include "../../includes/evars.h"
#include "../../includes/minishell.h"

char	**free_previous_args(char **tofree, int i)
{
	int	j;

	j = 0;
	while (j < i)
		free(tofree[j++]);
	free(tofree);
	perror_context("malloc", NULL);
	return (NULL);
}

static char	**init_cmd_array(t_cmd *cmd)
{
	int		i;
	t_list	*args;
	char	**res;

	i = 0;
	args = cmd->cmd_args;
	res = malloc(sizeof(char *) * (ft_lstsize(args) + 1));
	if (!res)
		return (NULL);
	while (args)
	{
		res[i] = ft_strdup(args->content);
		if (!res[i])
			return (free_previous_args(res, i));
		args = args->next;
		i++;
	}
	res[i] = NULL;
	return (res);
}

int	copy_all_cmds(t_list *head)
{
	int		i;
	t_list	*iter;
	t_cmd	*current_cmd;

	iter = head;
	i = 1;
	while (iter)
	{
		current_cmd = iter->content;
		current_cmd->nb = i++;
		current_cmd->command = init_cmd_array(current_cmd);
		if (!current_cmd->command)
			return (1);
		iter = iter->next;
	}
	return (0);
}
