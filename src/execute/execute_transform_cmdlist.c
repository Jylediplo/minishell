/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_transform_cmdlist.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lefabreg <lefabreg@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 23:39:10 by pantoine          #+#    #+#             */
/*   Updated: 2024/06/04 11:33:44 by pantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execute.h"
#include "../../includes/evars.h"
#include "../../includes/minishell.h"

static char	**free_previous_args(char **tofree, int i)
{
	int	j;

	j = 0;
	while (j < i)
		free(tofree[j++]);
	free(tofree);
	perror_context("malloc", NULL, 2);
	return (NULL);
}

static int	copy_arg(char **res, int *index, char *to_copy)
{
	res[*index] = ft_strdup(to_copy);
	if (!res[*index])
	{
		free_previous_args(res, *index);
		return (1);
	}
	*index += 1;
	return (0);
}

static char	**init_cmd_array(t_cmd *cmd)
{
	int		i;
	t_list	*args;
	char	**res;
	char	*cmd_arg;

	i = 0;
	args = cmd->cmd_args;
	res = malloc(sizeof(char *) * (ft_lstsize(args) + 1));
	if (!res)
	{
		perror_context("malloc", NULL, 2);
		return (NULL);
	}
	while (args)
	{
		cmd_arg = args->content;
		if (copy_arg(res, &i, cmd_arg))
			return (NULL);
		args = args->next;
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
