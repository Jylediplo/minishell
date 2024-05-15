/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_free_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pantoine <pantoine@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 22:52:53 by pantoine          #+#    #+#             */
/*   Updated: 2024/05/14 23:43:18 by pantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execute.h"
#include "../../includes/evars.h"
#include "../../includes/minishell.h"

void	close_fds_remove_tmps(t_cmd *cmd)
{
	if (cmd->tempfile_name)
		unlink(cmd->tempfile_name);
	free(cmd->tempfile_name);
}

void	free_single_cmd(t_list *args)
{
	t_list	*temp;

	while (args)
	{
		temp = args->next;
		free(args);
		args = temp;
	}
}

void	free_command_arrays(t_list *head)
{
	t_list	*iter;
	int		i;
	t_cmd	*content;
	char	**command;

	iter = head;
	i = 0;
	while (iter)
	{
		content = iter->content;
		command = content->command;
		if (command)
		{
			while (command[i])
				free(command[i++]);
			free(command);
		}
		i = 0;
		iter = iter->next;
	}
}

void	free_cmdlist(t_list *cmds)
{
	t_list	*iter;
	t_list	*temp;
	t_list	*args;
	t_cmd	*cmd;

	iter = cmds;
	cmd = iter->content;
	args = cmd->cmd_args;
	free(args->content);
	while (iter)
	{
		temp = iter->next;
		cmd = iter->content;
		args = cmd->cmd_args;
		free_single_cmd(args);
		close_fds_remove_tmps(cmd);
		free(cmd);
		free(iter);
		iter = temp;
	}
}

void	free_lexer(t_lexer **lexer)
{
	int	i;

	i = 0;
	while (lexer[i])
	{
		free(lexer[i]->content);
		free(lexer[i++]);
	}
	free(lexer);
}
