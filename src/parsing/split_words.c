/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_words.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lefabreg <lefabreg@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 14:24:01 by lefabreg          #+#    #+#             */
/*   Updated: 2024/05/31 22:27:42 by lefabreg         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_strncpy(char *dst, const char *src, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (i < ft_strlen(src))
			dst[i] = src[i];
		else
			dst[i] = '\0';
		i++;
	}
	return (dst);
}

void	handle_dolls(t_words *words, int *i)
{
	if (words->command[*i] == '$' && words->command[*i + 1] == '{'
		&& (!words->in_s_q && !words->in_db_q))
		words->in_dollar = 1;
	if (words->command[*i] == '}' && words->in_dollar)
		words->in_dollar = 0;
}

void	words_create(t_words *words, int *i, t_to_free *values, char *command)
{
	(words->words)[words->num_words] = malloc((*i - words->word_start + 1)
			* sizeof(char));
	if ((words->words)[words->num_words] == NULL)
	{
		split_words_free(words, values, command);
		write(2, "petitcoq: malloc: failure\n", 26);
		exit(1);
	}
	ft_strncpy((words->words)[words->num_words], words->command
		+ words->word_start, *i - words->word_start);
	(words->words)[words->num_words][*i - words->word_start] = '\0';
	(words->num_words)++;
}

void	create_words(t_words *words, int *i, t_to_free *values, char *command)
{
	while (*i < words->len)
	{
		handle_dolls(words, i);
		if (words->command[*i] == '"' || words->command[*i] == '\'')
		{
			if (words->command[*i] == '"' && (!words->in_s_q))
				words->in_db_q = !words->in_db_q;
			else if (words->command[*i] == '\'' && (!words->in_db_q))
				words->in_s_q = !words->in_s_q;
		}
		else if ((!words->in_s_q && !words->in_db_q && !words->in_dollar)
			&& (words->command[*i] == ' ' || words->command[*i] == '\t'))
		{
			if (*i > words->word_start)
				words_create(words, i, values, command);
			words->word_start = *i + 1;
		}
		(*i)++;
	}
}

void	split_words(t_words *words, t_to_free *values, char *command)
{
	int	i;

	i = 0;
	check_words(words, values, command);
	reset_values(words);
	create_words(words, &i, values, command);
	if (i > words->word_start && (!words->in_s_q && !words->in_db_q))
	{
		(words->words)[words->num_words] = malloc((i - words->word_start + 1)
				* sizeof(char));
		if ((words->words)[words->num_words] == NULL)
			split_words_free(words, values, command);
		ft_strncpy((words->words)[words->num_words], words->command
			+ words->word_start, i - words->word_start);
		(words->words)[words->num_words][i - words->word_start] = '\0';
		(words->num_words)++;
	}
	if (words->in_dollar)
		split_words_free(words, values, command);
}
