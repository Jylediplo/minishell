/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_init_structs.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pantoine <pantoine@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 21:08:36 by pantoine          #+#    #+#             */
/*   Updated: 2024/06/03 23:37:23 by pantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execute.h"
#include "../../includes/evars.h"
#include "../../includes/minishell.h"

static t_lexer	**remove_nulls(t_lexer **lexer, int size)
{
	int	i;
	int	j;
	int	count;
	t_lexer	**res;

	i = 0;
	j = 0;
	count = 0;
	res = NULL;
	while (i < size)
	{
		if (lexer[i++]->content)
			count++;
	}
	res = malloc(sizeof(t_lexer *) * (count + 1));
	i = 0;
	while (i < size)
	{
		if (lexer[i]->content)
			res[j++] = lexer[i];
		else
			free(lexer[i]);
		i++;
	}
	free(lexer);
	res[j] = NULL;
	return (res);
}

t_lexer	**init_lex(t_list *envp, t_lexer **lexer)
{
	int		i;
	int		size;

	i = 0;
	size = lexer[0]->size_lexer;
	while (i < size)
	{
		if (lexer[i]->e_flag == BUILTIN)
		{
			if (parse_builtin_sequence(lexer, &i, envp))
				return (NULL);
		}
		if (i < size && lexer[i]->dollar)
		{
			if (parse_dollar_sequence(lexer, &i, envp))
				return (NULL);
		}
		if (i++ == size)
			break ;
	}
	return (remove_nulls(lexer, size));
}

static t_list	*create_begin_cmd(t_cmd *begin_cmd, char *begin)
{
	t_list	*head;

	if (!begin_cmd->cmd_args)
	{
		perror_context("malloc", NULL, 2);
		free(begin);
		free(begin_cmd);
		return (NULL);
	}
	head = ft_lstnew(begin_cmd);
	if (!head)
	{
		perror_context("malloc", NULL, 2);
		free(begin);
		free(begin_cmd->cmd_args);
		free(begin_cmd);
		return (NULL);
	}
	return (head);
}

t_list	*init_cmdlist_size(t_lexer **lexer)
{
	char	*begin;
	t_cmd	*first_cmd;

	first_cmd = malloc(sizeof(t_cmd));
	if (!first_cmd)
	{
		perror_context("malloc", NULL, 2);
		free_lexer(lexer);
		return (NULL);
	}
	first_cmd->in = NULL;
	first_cmd->out = NULL;
	first_cmd->tempfile_name = NULL;
	first_cmd->command = NULL;
	begin = ft_strdup("BEGIN");
	if (!begin)
	{
		perror_context("malloc", NULL, 2);
		free(first_cmd);
		free_lexer(lexer);
		return (NULL);
	}
	first_cmd->cmd_args = ft_lstnew(begin);
	return (create_begin_cmd(first_cmd, begin));
}
