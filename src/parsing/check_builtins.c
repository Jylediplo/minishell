/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyjy <jyjy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 15:10:28 by lefabreg          #+#    #+#             */
/*   Updated: 2024/05/31 00:39:58 by jyjy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	check_for_previous_builtins(t_words *words, int *previous_is_builtin,
		t_lexer **lexer, t_to_free *values)
{
	int	has_quotes;

	has_quotes = 0;
	if (!(*previous_is_builtin))
	{
		lexer[values->i]->content = manage_quotes(words->wds_delim[values->i],
				&has_quotes);
		if (has_quotes)
			lexer[values->i]->quote_removed = 1;
		if (!lexer[values->i]->content)
		{
			free_lexer1(words, values->i);
			split_words_free(words, values->envp, values->command);
		}
	}
	else
	{
		lexer[values->i]->content = ft_strdup(words->wds_delim[values->i]);
		if (!lexer[values->i]->content)
		{
			free_lexer1(words, values->i);
			split_words_free(words, values->envp, values->command);
		}
	}
}

static void	fill_builtins(char **builtins)
{
	builtins[0] = "echo";
	builtins[1] = "cd";
	builtins[2] = "pwd";
	builtins[3] = "export";
	builtins[4] = "unset";
	builtins[5] = "env";
	builtins[6] = "exit";
}

int	is_builtin1(char *word, t_words *words, t_to_free *values)
{
	char	**builtins;
	int		i;

	builtins = malloc(sizeof(char *) * 7);
	if (!builtins)
	{
		free_lexer1(words, values->i);
		split_words_free(words, values->envp, values->command);
	}
	fill_builtins(builtins);
	i = 0;
	while (i < 7)
	{
		if (!ft_strncmp(word, builtins[i], ft_strlen(word))
			&& (ft_strlen(word) == ft_strlen(builtins[i])))
			return (free(builtins), 1);
		i++;
	}
	free(builtins);
	return (0);
}

int	is_matching(char *word, char *token, size_t length, int *previous)
{
	if (!word)
		return (0);
	if (!ft_strncmp(word, token, ft_strlen(word))
		&& (ft_strlen(word) == length))
	{
		if (!ft_strncmp(word, "|", ft_strlen(word)))
			*previous = 0;
		return (1);
	}
	return (0);
}

int	is_builtin(char *word)
{
	char	**builtins;
	int		i;

	builtins = malloc(sizeof(char *) * 7);
	if (!builtins)
	{
		printf("error Malloc, free avec ce que t as besoin\n");
		exit(1);
	}
	fill_builtins(builtins);
	i = 0;
	while (i < 7)
	{
		if (!ft_strncmp(word, builtins[i], ft_strlen(word))
			&& (ft_strlen(word) == ft_strlen(builtins[i])))
			return (free(builtins), 1);
		i++;
	}
	free(builtins);
	return (0);
}
