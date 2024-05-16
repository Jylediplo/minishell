/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_delim1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lefabreg <lefabreg@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 17:20:24 by lefabreg          #+#    #+#             */
/*   Updated: 2024/05/16 17:37:43 by lefabreg         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_sentence(char **sentence)
{
	int	i;

	i = 0;
	while (sentence[i])
	{
		free(sentence[i++]);
	}
	free(sentence);
}

void	free_delim_creation(t_delims **delims, char **sentence,
		t_to_free *values)
{
	free_delim(delims);
	free_sentence(sentence);
	split_words_free(values->words, values->envp, values->command);
}

void	manage_first_delim(t_del *del, char *word, t_delims **delims)
{
	del->count++;
	if (word[delims[del->i]->index - 1] != '\0')
		del->count++;
	if (word[delims[del->i]->index + ft_strlen(delims[del->i]->delim)] != '\0'
		&& word[delims[del->i]->index
			+ ft_strlen(delims[del->i]->delim)] != delim(del->delimiter,
				word[delims[del->i]->index + 1]))
		del->count++;
}

void	delimiter(char *word)
{
	char	*delimiter;
	int	db_quote_open;
	int	s_quote_open;
	int	i;

	db_quote_open = 0;
	s_quote_open = 0;
	i = 0;
    delimiter = "><|";
	while (word[i])
	{
		if (word[i] == '"' || word[i] == '\'')
		{
			if (word[i] == '\'')
				s_quote_open = !s_quote_open;
			else
				db_quote_open = !db_quote_open;
		}
		if (word[i] == delim(delimiter, word[i]) && (!s_quote_open
				&& !db_quote_open))
		{
			if (word[i + 1] == delim(delimiter, word[i]) && word[i] != '|')
				i++;
		}
		i++;
	}
}
