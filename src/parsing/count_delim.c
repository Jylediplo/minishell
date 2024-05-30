/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_delim.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyjy <jyjy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 15:02:55 by lefabreg          #+#    #+#             */
/*   Updated: 2024/05/31 00:35:49 by jyjy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	init_del(t_del *del, int nb_delim)
{
	del->i = -1;
	del->count = 0;
	del->delimiter = "<>|";
	del->nb_delim = nb_delim;
	del->s_quote_open = 0;
	del->db_quote_open = 0;
}

static void	manage_last_delim(t_del *del, char *word, t_delims **delims)
{
	del->count += 1;
	if ((word[delims[del->i]->index - 1] != '\0')
		&& (word[delims[del->i]->index - 1]
			!= delim(del->delimiter, word[delims[del->i]->index - 1])))
		del->count += 1;
	if ((word[delims[del->i]->index + ft_strlen(delims[del->i]->delim)]
			!= '\0')
		&& word[delims[del->i]->index
			+ ft_strlen(delims[del->i]->delim)] != delim(del->delimiter,
			word[delims[del->i]->index + 1]))
		del->count += 1;
}

static void	manage_inter_delim(t_del *del, char *word, t_delims **delims)
{
	del->count += 1;
	if (delims[del->i]->index != 0)
	{
		if (word[delims[del->i]->index - 1] != '\0'
			&& word[delims[del->i]->index - 1] != delim(del->delimiter,
				word[delims[del->i]->index - 1]))
			del->count += 1;
	}
	else if (del->nb_delim == 1 && word[delims[del->i]->index
			+ ft_strlen(delims[del->i]->delim)] != '\0')
		del->count += 1;
}

int	count_with_delim(t_delims **delims, int nb_delim, char *word)
{
	t_del	del;

	init_del(&del, nb_delim);
	while (delims[++del.i])
	{
		if (del.i == 0 && del.i == nb_delim - 1 && delims[del.i]->index != 0)
			manage_first_delim(&del, word, delims);
		else if (del.i == 0 && delims[del.i]->index != 0)
		{
			del.count++;
			if (word[delims[del.i]->index - 1] != '\0')
				del.count++;
		}
		else if (del.i == nb_delim - 1 && delims[del.i]->index != 0)
			manage_last_delim(&del, word, delims);
		else
			manage_inter_delim(&del, word, delims);
	}
	return (del.count);
}

int	count_delim(char *word)
{
	t_del	del;

	init_del(&del, 0);
	while (word[++del.i])
	{
		if (word[del.i] == '"' || word[del.i] == '\'')
		{
			if (word[del.i] == '\'')
				del.s_quote_open = !(del.s_quote_open);
			else
				del.db_quote_open = !(del.db_quote_open);
		}
		if (word[del.i] == delim(del.delimiter, word[del.i])
			&& (!(del.s_quote_open) && !(del.db_quote_open)))
		{
			if (word[del.i + 1] == delim(del.delimiter, word[del.i])
				&& word[del.i] != '|')
				del.i++;
			del.count++;
		}
	}
	return (del.count);
}
