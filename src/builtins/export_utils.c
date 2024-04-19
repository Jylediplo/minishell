/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pantoine <pantoine@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 10:32:52 by pantoine          #+#    #+#             */
/*   Updated: 2024/04/19 21:29:57 by pantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/evars.h"

int	allowed_in_substitution(char c)
{
	if (!c)
		return (0);
	if ((c >= 48 && c <= 57)
		|| (c >= 65 && c <= 90)
		|| (c == 95)
		|| (c >=97 && c <= 122))
		return (1);
	return (0);
}

void	copy_char(t_evar *evar)
{
	evar->newvalue_toset[evar->id_toset++]
		= evar->newvalue_copy[evar->id_copy++];
}

char	current_char(t_evar *evar)
{
	return (evar->newvalue_copy[evar->id_copy]);
}

void	copy_quoted_sequence(t_evar *evar, char quotetype)
{
	while (current_char(evar) != quotetype)
	{
		if (current_char(evar) == '$')
			expand_dol(evar);
		else if (current_char(evar) == ' ')
			return (set_err_status(evar, STOP));
		else
			copy_char(evar);
		if (evar->error == MALLOC)
			return ;
	}
	evar->id_copy++;
	while (current_char(evar) != quotetype)
	{
		if (current_char(evar) == '$' && quotetype == '\"')
			expand_dol(evar);
		else
			copy_char(evar);
		if (evar->error == MALLOC)
			return ;
	}
	if (current_char(evar))
		evar->id_copy++;
}

void	find_next_quotes(t_evar *evar, char *string, int index)
{
	evar->single_qchar = ft_strchr(string + index, '\'');
	evar->double_qchar = ft_strchr(string + index, '\"');
}

void	get_evar(t_evar *evar)
{
	find_next_quotes(evar, evar->newvalue_copy, evar->id_copy);
	while (current_char(evar))
	{
		get_next_quotetype(evar);
		if (evar->quotetype)
			copy_quoted_sequence(evar, evar->quotetype);
		else if (!evar->double_qchar && !evar->single_qchar)
		{
			if (current_char(evar) == '$')
				expand_dol(evar);
			else if (current_char(evar) == ' ')
				break ;
			else
				copy_char(evar);
		}
		if (evar->error == STOP || evar->error == MALLOC)
			return ;
		find_next_quotes(evar, evar->newvalue_copy, evar->id_copy);
	}
	evar->newvalue_toset[evar->id_toset] = '\0';
}
