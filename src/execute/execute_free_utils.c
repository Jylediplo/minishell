/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_free_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pantoine <pantoine@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 22:52:53 by pantoine          #+#    #+#             */
/*   Updated: 2024/05/24 12:13:20 by pantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execute.h"
#include "../../includes/evars.h"
#include "../../includes/minishell.h"

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

void	free_outfiles(t_cmd *cmd)
{
	t_list		*iter;
	t_list		*temp;

	if (!cmd->out)
		return ;
	iter = cmd->out;
	while (iter)
	{
		temp = iter->next;
		free(iter->content);
		free(iter);
		iter = temp;
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
		free_outfiles(cmd);
		if (cmd->tempfile_name)
			unlink(cmd->tempfile_name);
		free(cmd->tempfile_name);
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
