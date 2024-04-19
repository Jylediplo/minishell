/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_substitutions.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pantoine <pantoine@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 21:18:33 by pantoine          #+#    #+#             */
/*   Updated: 2024/04/19 21:20:44 by pantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/evars.h"

void	get_expanded_size(t_evar *evar)
{
	evar->dol_expansion_variable
		= (char *)malloc(sizeof(char) * (evar->size_expanded_var + 1));
	if (!evar->dol_expansion_variable)
		return (set_err_status(evar, MALLOC));
	ft_memcpy(evar->dol_expansion_variable,
		   evar->newvalue - evar->size_expanded_var,
		   evar->size_expanded_var);
	evar->dol_expansion_variable[evar->size_expanded_var] = '\0';
	evar->dol_expansion_value = getenv(evar->dol_expansion_variable);
	if (evar->dol_expansion_value)
		evar->size_evar += ft_strlen(evar->dol_expansion_value);
	if (*evar->newvalue == '}')
		evar->newvalue++;
	free(evar->dol_expansion_variable);
}

void	size_dol_substitution(t_evar *evar)
{
	evar->size_expanded_var = 0;
	evar->newvalue++;
	if (*evar->newvalue == '{')
	{
		evar->newvalue++;
		while (*evar->newvalue != '}')
		{
			if (!allowed_in_braces(*evar->newvalue))
				return (set_err_status(evar, BAD_SUBSTITUTION));
			else
				increase_expanded_var_size(evar);
		}
	}
	else if (*evar->newvalue != '{')
	{
		while (allowed_in_substitution(*evar->newvalue)) //CHECK ALL VALID IDENTIFIERS
			increase_expanded_var_size(evar);
		if (!evar->size_expanded_var) //single dollar sign
		{
			evar->size_evar++;
			return ;
		}
	}
	get_expanded_size(evar);
}

void	substitute_var(t_evar *evar)
{
	evar->dol_expansion_variable
		= (char *)malloc(sizeof(char) * (evar->size_expanded_var + 1));
	if (!evar->dol_expansion_variable)
		return (malloc_error_dol(evar));
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
		if (!evar->size_expanded_var) //single dollar sign
		{
			evar->id_copy--;
			copy_char(evar);
			return ;
		}
	}
	substitute_var(evar);
}
