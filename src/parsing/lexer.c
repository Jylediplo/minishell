/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lefabreg <lefabreg@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 14:56:34 by lefabreg          #+#    #+#             */
/*   Updated: 2024/06/03 19:59:31 by lefabreg         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	create_lexer(t_words *words, int *previous_is_builtin, t_lexer **lexer,
		t_to_free *values)
{
	check_for_previous_builtins(words, previous_is_builtin, lexer, values);
	if (is_matching(words->wds_delim[values->i], "|", 1, previous_is_builtin))
		lexer[values->i]->e_flag = PIPE;
	else if (is_matching(words->wds_delim[values->i], ">", 1,
			previous_is_builtin))
		lexer[values->i]->e_flag = GREATER;
	else if (is_matching(words->wds_delim[values->i], "<", 1,
			previous_is_builtin))
		lexer[values->i]->e_flag = LESSER;
	else if (is_matching(words->wds_delim[values->i], "<<", 2,
			previous_is_builtin))
		lexer[values->i]->e_flag = HEREDOC;
	else if (is_matching(words->wds_delim[values->i], ">>", 2,
			previous_is_builtin))
		lexer[values->i]->e_flag = APPEND;
	else
	{
		lexer[values->i]->e_flag = WORD;
		if (is_builtin1(lexer[values->i]->content, words, values))
		{
			lexer[values->i]->e_flag = BUILTIN;
			*previous_is_builtin = 1;
		}
	}
}

void	handle_lexer(t_words *words, int *previous_is_builtin,
		t_to_free *values)
{
	values->i = -1;
	words->lexer = malloc(sizeof(t_lexer *) * (words->count_del + 1));
	if (!words->lexer)
		split_words_free(words, values, values->command);
	while (++values->i < words->count_del)
	{
		words->lexer[values->i] = malloc(sizeof(t_lexer) * 1);
		if (!words->lexer[values->i])
		{
			split_words_free(words, values, values->command);
			free(words->lexer);
		}
		words->lexer[values->i]->size_lexer = words->count_del;
		words->lexer[values->i]->quote_removed = 0;
		words->lexer[values->i]->dollar = 0;
		if (count_dollars(words->wds_delim[values->i]))
			dollars_handler(words->lexer, values, words, previous_is_builtin);
		else
			create_lexer(words, previous_is_builtin, words->lexer, values);
	}
	*previous_is_builtin = 0;
	words->lexer[values->i] = 0;
}

void	copy_to_wds_delim(int *b, char **word, t_words *words,
		t_to_free *values)
{
	int	d;
	int	k;

	d = 0;
	while (word[d])
	{
		words->wds_delim[*b] = ft_strdup(word[d]);
		if (!words->wds_delim[*b])
		{
			k = 0;
			while (word[k])
				free(word[k++]);
			free(word);
			split_words_free(words, values, values->command);
		}
		free(word[d]);
		*b += 1;
		d++;
	}
	free(word[d]);
	free(word);
}

void	manage_if_no_delim(char ***word, t_to_free *values, t_words *words,
		int i)
{
	t_delims	**delim;
	int			nb_delim;

	nb_delim = count_delim(words->words[i]);
	delim = create_tab_delim(words->words[i], nb_delim, values, words);
	if (!delim)
		split_words_free(words, values, values->command);
	values->nb_words = count_with_delim(delim, nb_delim, words->words[i]);
	*word = create_words_tab(delim, nb_delim, words->words[i], values);
	if (!*word)
	{
		free_delim(delim);
		split_words_free(words, values, values->command);
	}
	free_delim(delim);
}

void	create_wds_lexer(t_words *words, t_to_free *values)
{
	char	**word;
	int		b;
	int		i;

	b = 0;
	i = -1;
	while (++i < words->num_words)
	{
		manage_if_no_delim(&word, values, words, i);
		if (!values->nb_words)
		{
			free_temp_word(word);
			word = malloc(sizeof(char *) * 2);
			if (!word)
				split_words_free(words, values, values->command);
			word[0] = ft_strdup(words->words[i]);
			if (!word[0])
			{
				free(word);
				split_words_free(words, values, values->command);
			}
			word[1] = NULL;
		}
		copy_to_wds_delim(&b, word, words, values);
	}
}
