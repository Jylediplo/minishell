/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_init_structs_utils.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pantoine <pantoine@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 10:46:13 by pantoine          #+#    #+#             */
/*   Updated: 2024/06/04 12:39:33 by pantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execute.h"
#include "../../includes/evars.h"
#include "../../includes/minishell.h"

int	parse_builtin_sequence(t_lexer **lexer, int *index, t_list *envp)
{
	char	*temp;
	int		size;

	size = lexer[*index]->size_lexer;
	*index += 1;
	while (*index < size && lexer[*index]->e_flag != PIPE)
	{
		temp = parse_echo(envp, lexer[*index]->content, 2);
		if (!temp)
		{
			free_lexer(lexer);
			return (1);
		}
		free(lexer[*index]->content);
		lexer[*index]->content = temp;
		*index += 1;
	}
	return (0);
}

int	replace_parsed_content(t_lexer **lexer,
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
		if (!newval[0] && !ft_strchr(lexer[*index]->content, '\"'))
		{
			free(newval);
			free(lexer[*index]->content);
			lexer[*index]->content = NULL;
			return (0);
		}
		free(lexer[*index]->content);
		lexer[*index]->content = newval;
	}
	return (0);
}

int	parse_dollar_sequence(t_lexer **lexer, int *index, t_list *envp)
{
	char	*temp;
	int		has_quotes;

	has_quotes = 0;
	if (*index - 1 >= 0)
	{
		if (lexer[*index - 1]->e_flag == HEREDOC)
			temp = manage_quotes_pantoine(lexer[*index]->content, &has_quotes);
		else
			temp = parse_echo(envp, lexer[*index]->content, 2);
	}
	else
		temp = parse_echo(envp, lexer[*index]->content, 2);
	if (!temp)
	{
		free_lexer(lexer);
		return (1);
	}
	if (replace_parsed_content(lexer, index, temp, envp))
		return (1);
	return (0);
}
