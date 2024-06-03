/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_words.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lefabreg <lefabreg@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 14:28:36 by lefabreg          #+#    #+#             */
/*   Updated: 2024/06/03 15:15:30 by lefabreg         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_wds_delim(t_words *words, int nb)
{
	int	i;

	i = 0;
	while (i < nb)
	{
		free(words->wds_delim[i++]);
	}
	free(words->wds_delim[i]);
	free(words->wds_delim);
}

void	free_words(t_words *words)
{
	int	i;

	i = 0;
	while (i < words->num_words)
	{
		free(words->words[i++]);
	}
	free(words->words);
}

void	free_temp_word(char **word)
{
	int	i;

	i = 0;
	while (word[i])
	{
		free(word[i]);
		i++;
	}
	free(word[i]);
	free(word);
}

void	free_lexer1(t_words *words, int index)
{
	int	i;

	i = 0;
	while (i < index)
	{
		if (words->lexer[i]->content)
			free(words->lexer[i]->content);
		free(words->lexer[i]);
		i++;
	}
	free(words->lexer[i]->content);
	free(words->lexer[i]);
	free(words->lexer);
}

void	free_delim(t_delims **delim)
{
	int	i;

	i = 0;
	while (delim[i])
	{
		free(delim[i]->delim);
		free(delim[i]);
		i++;
	}
	free(delim[i]);
	free(delim);
}
