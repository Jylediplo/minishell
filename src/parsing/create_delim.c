/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_delim.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lefabreg <lefabreg@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 15:06:48 by lefabreg          #+#    #+#             */
/*   Updated: 2024/05/16 16:50:05 by lefabreg         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

typedef struct s_cwds
{
	char	**sentence;
	int		i;
	int		j;
	int		count;
}			t_cwds;

static void	words_tab_creation(t_cwds *wds, t_delims **delims, char *word,
		t_to_free *values)
{
	(void)word;
	wds->sentence[wds->count] = ft_substr(word, wds->j, (delims[wds->i]->index
				- wds->j));
	if (!wds->sentence[wds->count])
		free_delim_creation(delims, wds->sentence, values);
	if (!*wds->sentence[wds->count])
	{
		free(wds->sentence[wds->count]);
		wds->sentence[wds->count] = ft_strdup(delims[wds->i]->delim);
		if (!wds->sentence[wds->count])
			free_delim_creation(delims, wds->sentence, values);
	}
	else
	{
		wds->count += 1;
		wds->sentence[wds->count] = ft_strdup(delims[wds->i]->delim);
		if (!wds->sentence[wds->count])
			free_delim_creation(delims, wds->sentence, values);
	}
	wds->j = delims[wds->i]->index + ft_strlen(delims[wds->i]->delim);
}

static void	init_cwds(t_cwds *wds, t_to_free *values, t_delims **delims)
{
	wds->i = 0;
	wds->j = 0;
	wds->count = 0;
	wds->sentence = malloc(sizeof(char *) * (values->nb_words + 1));
	if (!wds->sentence)
	{
		free_delim(delims);
		split_words_free(values->words, values->envp, values->command);
	}
	wds->sentence[values->nb_words] = NULL;
}

char	**create_words_tab(t_delims **delims, int nb_delim, char *word,
		t_to_free *values)
{
	t_cwds wds;

	init_cwds(&wds, values, delims);
	while (delims[wds.i])
	{
		words_tab_creation(&wds, delims, word, values);
		if (wds.i == nb_delim - 1 && word[delims[wds.i]->index
			+ ft_strlen(delims[wds.i]->delim)] != '\0')
		{
			free(wds.sentence[wds.count]);
			wds.sentence[wds.count] = ft_strdup(delims[wds.i]->delim);
			if (!wds.sentence[wds.count])
				free_delim_creation(delims, wds.sentence, values);
			wds.count++;
			wds.sentence[wds.count] = ft_substr(word, delims[wds.i]->index
					+ ft_strlen(delims[wds.i]->delim), (ft_strlen(word)
						- delims[wds.i]->index));
			if (!wds.sentence[wds.count])
				free_delim_creation(delims, wds.sentence, values);
		}
		wds.count++;
		wds.i++;
	}
	return (wds.sentence);
}
