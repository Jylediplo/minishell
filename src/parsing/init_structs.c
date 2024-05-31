/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_structs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lefabreg <lefabreg@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 14:49:47 by lefabreg          #+#    #+#             */
/*   Updated: 2024/05/31 22:19:09 by lefabreg         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	reset_values(t_words *words)
{
	words->num_words = 0;
	words->in_s_q = 0;
	words->in_db_q = 0;
	words->word_start = 0;
}

void	init_words_struct(t_words *words, char *command)
{
	words->len = ft_strlen(command);
	words->in_s_q = 0;
	words->in_dollar = 0;
	words->in_db_q = 0;
	words->word_start = 0;
	words->num_words = 0;
	words->count_del = 0;
	words->command = command;
}

void	init_struct_del(t_delim *delim, char *str)
{
	delim->del = "<|>";
	delim->start = str;
	delim->end = str;
	delim->index = 0;
	delim->tokens = malloc((ft_strlen(str) + 1) * sizeof(char *));
	if (!delim->tokens)
	{
		write(2, "petitcoq: malloc: failure\n", 26);
		exit(1);
	}
}
