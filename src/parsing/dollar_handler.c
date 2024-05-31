/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lefabreg <lefabreg@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 14:52:20 by lefabreg          #+#    #+#             */
/*   Updated: 2024/05/31 23:47:46 by lefabreg         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	dollars_handler(t_lexer **lexer, t_to_free *values, t_words *words,
		int *previous)
{
	lexer[values->i]->dollar = 1;
	lexer[values->i]->e_flag = WORD;
	lexer[values->i]->content = ft_strdup(words->wds_delim[values->i]);
	if (!lexer[values->i]->content)
	{
		split_words_free(words, values, values->command);
		free_lexer1(words, values->i);
		write(2, "petitcoq: malloc: failure\n", 26);
		exit(1);
	}
	if (values->i == 0)
		*previous = 1;
}

int	count_dollars(char *word)
{
	int	i;

	i = 0;
	while (word && word[i])
	{
		if (word[i] == '$')
			return (1);
		i++;
	}
	return (0);
}
