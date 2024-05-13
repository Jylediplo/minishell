/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_init_structs.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pantoine <pantoine@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 21:08:36 by pantoine          #+#    #+#             */
/*   Updated: 2024/05/13 23:25:59 by pantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execute.h"
#include "../../includes/evars.h"
#include "../../includes/minishell.h"

t_lexer	**init_lex(t_list *envp, t_lexer **lexer)
{
	char	*temp;
	int		i;

	i = 0;
	while (lexer[i])
	{
		if (lexer[i]->dollar)
		{
			temp = parse_echo(envp, lexer[i]->content);
			if (!temp)
			{
				free_current_lexer(lexer, i);
				return (NULL);
			}
			if (is_builtin(temp))
				lexer[i]->flag = BUILTIN;
			free(lexer[i]->content);
			lexer[i]->content = temp;
		}
		i++;
	}
	return (lexer);
}

t_list	*create_begin_cmd(t_cmd *begin_cmd, char *begin)
{
	t_list	*head;

	if (!begin_cmd->cmd_args)
	{
		perror_context("malloc", NULL);
		free(begin);
		free(begin_cmd);
		return (NULL);
	}
	head = ft_lstnew(begin_cmd);
	if (!head)
	{
		perror_context("malloc", NULL);
		free(begin);
		free(begin_cmd->cmd_args);
		free(begin_cmd);
		return (NULL);
	}
	return (head);
}

t_list	*init_cmdlist_size(void)
{
	char	*begin;
	t_cmd	*first_cmd;

	first_cmd = malloc(sizeof(t_cmd));
	if (!first_cmd)
	{
		perror_context("malloc", NULL);
		return (NULL);
	}
	first_cmd->in = NULL;
	first_cmd->out = NULL;
	first_cmd->tempfile_name = NULL;
	first_cmd->command = NULL;
	begin = ft_strdup("BEGIN");
	if (!begin)
	{
		perror_context("malloc", NULL);
		free(first_cmd);
		return (NULL);
	}
	first_cmd->cmd_args = ft_lstnew(begin);
	return (create_begin_cmd(first_cmd, begin));
}
