/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_transform_cmdlist.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pantoine <pantoine@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 23:39:10 by pantoine          #+#    #+#             */
/*   Updated: 2024/05/26 11:10:50 by pantoine         ###   ########.fr       */
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
	perror_context("malloc", NULL);
	return (NULL);
}

static int	count_nonempty_args(t_list *args)
{
	int		res;
	t_list	*iter;
	char	*cmd_arg;

	iter = args;
	res = 0;
	while (iter)
	{
		cmd_arg = iter->content;
		if (cmd_arg[0])
			res++;
		iter = iter->next;
	}
	return (res);
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
	res = malloc(sizeof(char *) * (count_nonempty_args(args) + 1));
	if (!res)
	{
		perror_context("malloc", NULL);
		return (NULL);
	}
	while (args)
	{
		cmd_arg = args->content;
		if (cmd_arg[0])
		{
			if (copy_arg(res, &i, cmd_arg))
				return (NULL);
		}
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
