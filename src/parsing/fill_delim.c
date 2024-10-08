/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_delim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lefabreg <lefabreg@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 18:25:20 by lefabreg          #+#    #+#             */
/*   Updated: 2024/05/31 23:50:44 by lefabreg         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	init_store_delim(t_store_delim *stk, int nb_delim,
	t_to_free *values, t_words *words)
{
	stk->db_quote_open = 0;
	stk->s_quote_open = 0;
	stk->i = 0;
	stk->delimiter = "><|";
	stk->cursor_tab = 0;
	stk->delims = malloc(sizeof(t_delims *) * (nb_delim + 1));
	if (!stk->delims)
	{
		free_words(words);
		free_envp(values->shell->envp);
		ft_lstclear(&values->shell->history.list, free_history_data);
		write(2, "petitcoq: malloc: failure\n", 26);
		exit(1);
	}
	stk->delims[nb_delim] = 0;
}

static void	store_db_delim(t_store_delim *stk, char *word, t_to_free *values,
		t_words *words)
{
	stk->delims[stk->cursor_tab] = malloc(sizeof(t_delims) * 1);
	if (!stk->delims[stk->cursor_tab])
	{
		free_delim(stk->delims);
		split_words_free(words, values, values->command);
	}
	stk->delims[stk->cursor_tab]->delim = malloc(sizeof(char) * (3));
	if (!stk->delims[stk->cursor_tab]->delim)
	{
		free_delim(stk->delims);
		split_words_free(words, values, values->command);
	}
	stk->delims[stk->cursor_tab]->delim[0] = delim(stk->delimiter,
			word[stk->i]);
	stk->delims[stk->cursor_tab]->delim[1] = delim(stk->delimiter,
			word[stk->i]);
	stk->delims[stk->cursor_tab]->delim[2] = '\0';
	stk->delims[stk->cursor_tab]->index = stk->i;
	stk->cursor_tab++;
	stk->i++;
}

static void	store_s_delim(t_store_delim *stk, char *word, t_to_free *values,
		t_words *words)
{
	stk->delims[stk->cursor_tab] = malloc(sizeof(t_delims) * 1);
	if (!stk->delims[stk->cursor_tab])
	{
		free_delim(stk->delims);
		split_words_free(words, values, values->command);
	}
	stk->delims[stk->cursor_tab]->delim = malloc(sizeof(char) * (2));
	if (!stk->delims[stk->cursor_tab]->delim)
	{
		free_delim(stk->delims);
		split_words_free(words, values, values->command);
	}
	stk->delims[stk->cursor_tab]->delim[0] = delim(stk->delimiter,
			word[stk->i]);
	stk->delims[stk->cursor_tab]->delim[1] = '\0';
	stk->delims[stk->cursor_tab]->index = stk->i;
	stk->cursor_tab++;
}

t_delims	**create_tab_delim(char *word, int nb_delim, t_to_free *values,
		t_words *words)
{
	t_store_delim	stk;

	init_store_delim(&stk, nb_delim, values, words);
	while (word[stk.i])
	{
		if (word[stk.i] == '"' || word[stk.i] == '\'')
		{
			if (word[stk.i] == '\'')
				stk.s_quote_open = !stk.s_quote_open;
			else
				stk.db_quote_open = !stk.db_quote_open;
		}
		if (word[stk.i] == delim(stk.delimiter, word[stk.i])
			&& (!stk.s_quote_open && !stk.db_quote_open))
		{
			if (word[stk.i + 1] == delim(stk.delimiter, word[stk.i])
				&& word[stk.i] != '|')
				store_db_delim(&stk, word, values, words);
			else
				store_s_delim(&stk, word, values, words);
		}
		stk.i++;
	}
	return (stk.delims);
}
