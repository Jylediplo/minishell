/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pantoine <pantoine@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 10:32:52 by pantoine          #+#    #+#             */
/*   Updated: 2024/04/17 16:00:29 by pantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	expand_dol(t_evar *evar)
{
	evar->id_copy++;
	if (evar->newvalue_copy[evar->id_copy] == '{')
	{
		evar->id_copy++;
		while (evar->newvalue_copy[evar->id_copy] != '}')
			evar->id_copy++;
	}
	else if (evar->newvalue_copy[evar->id_copy] != '{')
	{
		while (evar->newvalue_copy[evar->id_copy] != ' ' && evar->newvalue_copy[evar->id_copy] != '\"'
				&& evar->newvalue_copy[evar->id_copy])
			evar->id_copy++;
	}
	evar->dol_expansion_variable = (char *)malloc(sizeof(char) * (evar->size_expanded_var + 1));
	if (!evar->dol_expansion_variable)
	{
		evar->error = MALLOC;
		return ;
	}
	ft_memcpy(evar->dol_expansion_variable, evar->newvalue_copy - evar->size_expanded_var + evar->id_copy, evar->size_expanded_var);
	evar->dol_expansion_variable[evar->size_expanded_var] = '\0';
	evar->dol_expansion_value = getenv(evar->dol_expansion_variable);
	if (evar->dol_expansion_value)
	{
		ft_memcpy(evar->newvalue_toset + evar->id_toset, evar->dol_expansion_value, ft_strlen(evar->dol_expansion_value));
		evar->id_toset += ft_strlen(evar->dol_expansion_value);
	}
	if (evar->newvalue_copy[evar->id_copy] == '}')
		evar->id_copy++;
	free(evar->dol_expansion_variable);
}

void	copy_quoted_sequence(t_evar *evar, char quotetype)
{
	while (evar->newvalue_copy[evar->id_copy] != quotetype)
	{
		if (evar->newvalue_copy[evar->id_copy] == '$')
			expand_dol(evar);
		else
			evar->newvalue_toset[evar->id_toset++] = evar->newvalue_copy[evar->id_copy++];
	}
	evar->id_copy++;
	while (evar->newvalue_copy[evar->id_copy] != quotetype)
	{
		if (evar->newvalue_copy[evar->id_copy] == '$' && quotetype == '\"')
			 expand_dol(evar);
		else
			evar->newvalue_toset[evar->id_toset++] = evar->newvalue_copy[evar->id_copy++];
	}
	if (evar->newvalue_copy[evar->id_copy])
		evar->id_copy++;
}

void	get_evar(t_evar *evar)
{
	evar->single_qchar = ft_strchr(evar->newvalue_copy + evar->id_copy, '\'');
	evar->double_qchar = ft_strchr(evar->newvalue_copy + evar->id_copy, '\"');
	while (evar->newvalue_copy[evar->id_copy])
	{
		if ((!evar->double_qchar && evar->single_qchar) || (evar->double_qchar > evar->single_qchar && evar->single_qchar))
			copy_quoted_sequence(evar, '\'');
		else if ((evar->double_qchar && !evar->single_qchar) || (evar->double_qchar < evar->single_qchar && evar->double_qchar))
			copy_quoted_sequence(evar, '\"');
		else if (!evar->double_qchar && !evar->single_qchar)
		{
			if (evar->newvalue_copy[evar->id_copy] == '$')
				expand_dol(evar);
			else
				evar->newvalue_toset[evar->id_toset++] = evar->newvalue_copy[evar->id_copy++];
		}
		if (!evar->newvalue_copy[evar->id_copy])
			break ;
		evar->double_qchar = ft_strchr(evar->newvalue_copy + evar->id_copy, '\"');
		evar->single_qchar = ft_strchr(evar->newvalue_copy + evar->id_copy, '\'');
	}
	evar->newvalue_toset[evar->id_toset] = '\0';
}
