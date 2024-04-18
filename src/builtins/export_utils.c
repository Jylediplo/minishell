/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pantoine <pantoine@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 10:32:52 by pantoine          #+#    #+#             */
/*   Updated: 2024/04/18 17:32:48 by pantoine         ###   ########.fr       */
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

void	substitute_var(t_evar *evar)
{
	evar->dol_expansion_variable
		= (char *)malloc(sizeof(char) * (evar->size_expanded_var + 1));
	if (!evar->dol_expansion_variable)
		return (set_err_status(evar, MALLOC));
	ft_memcpy(evar->dol_expansion_variable,
		evar->newvalue_copy - evar->size_expanded_var + evar->id_copy,
		evar->size_expanded_var);
	evar->dol_expansion_variable[evar->size_expanded_var] = '\0';
	evar->dol_expansion_value = getenv(evar->dol_expansion_variable);
	if (evar->dol_expansion_value)
	{
		ft_memcpy(evar->newvalue_toset + evar->id_toset,
			evar->dol_expansion_value,
			ft_strlen(evar->dol_expansion_value));
		evar->id_toset += ft_strlen(evar->dol_expansion_value);
	}
	if (current_char(evar) == '}')
		evar->id_copy++;
	free(evar->dol_expansion_variable);
}

void	expand_dol(t_evar *evar)
{
	evar->size_expanded_var = 0;
	evar->id_copy++;
	if (current_char(evar) == '{')
	{
		evar->id_copy++;
		while (current_char(evar) != '}')
		{
			evar->id_copy++;
			evar->size_expanded_var++;
		}
	}
	else if (current_char(evar) != '{')
	{
		while (allowed_in_substitution(current_char(evar)))
		{
			evar->id_copy++;
			evar->size_expanded_var++;
		}
	}
	substitute_var(evar);
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
	}
	evar->id_copy++;
	while (current_char(evar) != quotetype)
	{
		if (current_char(evar) == '$' && quotetype == '\"')
			expand_dol(evar);
		else
			copy_char(evar);
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
		if (evar->error == STOP)
			return ;
		if (!evar->newvalue_copy)
			return ;
		find_next_quotes(evar, evar->newvalue_copy, evar->id_copy);
	}
	evar->newvalue_toset[evar->id_toset] = '\0';
}
