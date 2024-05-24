/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_init_structs.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pantoine <pantoine@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 21:08:36 by pantoine          #+#    #+#             */
/*   Updated: 2024/05/24 15:20:11 by pantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execute.h"
#include "../../includes/evars.h"
#include "../../includes/minishell.h"

static int	parse_builtin_sequence(t_lexer **lexer, int *index, t_list *envp)
{
	char	*temp;

	*index += 1;
	while (lexer[*index] && lexer[*index]->e_flag != PIPE)
	{
		temp = parse_echo(envp, lexer[*index]->content);
		if (!temp)
		{
			free_current_lexer(lexer, *index);
			return (1);
		}
		free(lexer[*index]->content);
		lexer[*index]->content = temp;
		*index += 1;
	}
	return (0);
}

static int	replace_parsed_content(t_lexer **lexer,
		int *index, char *newval, t_list *envp)
{
	if (is_builtin(newval))
	{
		lexer[*index]->e_flag = BUILTIN;
		free(lexer[*index]->content);
		lexer[*index]->content = newval;
		if (parse_builtin_sequence(lexer, index, envp))
			return (1);
	}
	else
	{
		free(lexer[*index]->content);
		lexer[*index]->content = newval;
	}
	return (0);
}

t_lexer	**init_lex(t_list *envp, t_lexer **lexer)
{
	char	*temp;
	int		i;

	i = 0;
	while (lexer[i])
	{
		if (lexer[i]->e_flag == BUILTIN)
		{
			if (parse_builtin_sequence(lexer, &i, envp))
				return (NULL);
		}
		if (lexer[i] && lexer[i]->dollar)
		{
			temp = parse_echo(envp, lexer[i]->content);
			if (!temp)
			{
				free_current_lexer(lexer, i);
				return (NULL);
			}
			replace_parsed_content(lexer, &i, temp, envp);
		}
		if (!lexer[i++])
			break ;
	}
	return (lexer);
}

static t_list	*create_begin_cmd(t_cmd *begin_cmd, char *begin)
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
