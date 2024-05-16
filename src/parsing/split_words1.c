/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_words1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lefabreg <lefabreg@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 14:46:33 by lefabreg          #+#    #+#             */
/*   Updated: 2024/05/16 16:36:24 by lefabreg         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	split_words_free(t_words *words, t_list *envp, char *command)
{
	int	i;

	i = 0;
	free_envp(envp);
	if (words->words)
		free_words(words);
	if (words->wds_delim)
	{
		while (words->wds_delim[i])
			free(words->wds_delim[i++]);
		free(words->wds_delim);
	}
	free(command);
	printf("Error MALLOC !\n");
	exit(EXIT_FAILURE);
}

static void	check_dolls(t_words *words, int i)
{
	if (words->command[i] == '$' && words->command[i + 1] == '{'
		&& (!words->in_s_q && !words->in_db_q))
		words->in_dollar = 1;
	if (words->command[i] == '}' && words->in_dollar)
		words->in_dollar = 0;
}

static void	handle_quote_inside_quote(t_words *words, int i)
{
	if (words->command[i] == '"' && (!words->in_s_q))
		words->in_db_q = !words->in_db_q;
	else if (words->command[i] == '\'' && (!words->in_db_q))
		words->in_s_q = !words->in_s_q;
}

void	check_words(t_words *words, t_list *envp, char *command)
{
	int i;

	i = 0;
	while (i < words->len)
	{
		check_dolls(words, i);
		if (words->command[i] == '"' || words->command[i] == '\'')
			handle_quote_inside_quote(words, i);
		else if ((!words->in_s_q && !words->in_db_q && !words->in_dollar)
			&& (words->command[i] == ' ' || words->command[i] == '\t'))
		{
			if (i > words->word_start)
				words->num_words++;
			words->word_start = i + 1;
		}
		i++;
	}
	if (i > words->word_start && (!words->in_s_q && !words->in_db_q))
		(words->num_words)++;
	words->words = malloc((words->num_words) * sizeof(char *));
	if (!words->words)
		split_words_free(words, envp, command);
}
