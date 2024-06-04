/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lefabreg <lefabreg@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 17:56:02 by pantoine          #+#    #+#             */
/*   Updated: 2024/06/04 11:49:17 by pantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execute.h"
#include "../../includes/lexing.h"
#include "../../includes/minishell.h"

char	delim(char *delimiter, char letter)
{
	int	i;

	i = 0;
	while (delimiter[i])
	{
		if (delimiter[i] == letter)
			return (letter);
		i++;
	}
	return (0);
}

void	nb_words_with_delim(t_words *words, t_to_free *values)
{
	t_delims	**delim;
	int			nb_delim;
	int			i;
	int			nb_words;

	i = 0;
	while (i < words->num_words)
	{
		nb_delim = count_delim(words->words[i]);
		delim = create_tab_delim(words->words[i], nb_delim, values, words);
		if (!delim)
			split_words_free(words, values, values->command);
		nb_words = count_with_delim(delim, nb_delim, words->words[i]);
		if (!nb_delim)
			nb_words += 1;
		free_delim(delim);
		words->count_del += nb_words;
		i++;
	}
}

void	split_word(char *command, t_shell *shell)
{
	static int	previous_is_builtin;
	t_words		words;
	t_to_free	values;

	words.wds_delim = NULL;
	values.command = command;
	values.shell = shell;
	values.words = &words;
	init_words_struct(&words, command);
	if (check_quotes(command, &values))
		split_words(&words, &values, command);
	nb_words_with_delim(&words, &values);
	words.wds_delim = malloc(sizeof(char *) * (words.count_del + 1));
	if (!words.wds_delim)
		split_words_free(&words, &values, command);
	words.wds_delim[words.count_del] = NULL;
	create_wds_lexer(&words, &values);
	handle_lexer(&words, &previous_is_builtin, &values);
	free_wds_delim(&words, words.count_del);
	free_words(&words);
	if (!words.lexer[0])
		return (free(words.lexer), (void)0);
	get_cmdlist(words.lexer, shell);
}
