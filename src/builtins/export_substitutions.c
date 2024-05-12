/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_substitutions.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pantoine <pantoine@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 21:18:33 by pantoine          #+#    #+#             */
/*   Updated: 2024/05/12 19:45:54 by pantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/evars.h"

void	get_expanded_size(t_evar *evar, t_list *envp)
{
	if (get_exitsig_size(evar))
		return ;
	evar->dol_expansion_variable
		= (char *)malloc(sizeof(char) * (evar->size_expanded_var + 1));
	if (!evar->dol_expansion_variable)
		return (set_err_status(evar, MALLOC));
	ft_memcpy(evar->dol_expansion_variable,
		evar->newvalue - evar->size_expanded_var,
		evar->size_expanded_var);
	evar->dol_expansion_variable[evar->size_expanded_var] = '\0';
	evar->dol_expansion_value = get_envvar_value(&envp,
			evar->dol_expansion_variable);
	if (evar->dol_expansion_value)
		evar->size_evar += ft_strlen(evar->dol_expansion_value);
	if (*evar->newvalue == '}')
		evar->newvalue++;
	free(evar->dol_expansion_variable);
}

int	brace_size_dol_substitution(t_evar *evar, t_list *envp)
{
	evar->newvalue++;
	if (*evar->newvalue == '?')
	{
		trigger_exitsig_size_handler(evar, envp);
		return (1);
	}
	while (*evar->newvalue != '}' && *evar->newvalue)
	{
		if (!valid_identifier_char(*evar->newvalue))
		{
			set_err_status(evar, BAD_SUBSTITUTION);
			return (1);
		}
		else
			increase_expanded_var_size(evar);
	}
	if (*evar->newvalue != '}')
	{
		set_err_status(evar, UNCLOSED_BRACE);
		return (1);
	}
	return (0);
}

void	size_dol_substitution(t_evar *evar, int inside, t_list *envp)
{
	evar->size_expanded_var = 0;
	evar->newvalue++;
	if (*evar->newvalue == '{')
	{
		if (brace_size_dol_substitution(evar, envp))
			return ;
	}
	else if (*evar->newvalue != '{')
	{
		while (valid_identifier_char(*evar->newvalue))
			increase_expanded_var_size(evar);
		if (*evar->newvalue == '?')
			return (trigger_exitsig_size_handler(evar, envp));
		if (count_single_dollar(evar, inside))
			return ;
	}
	get_expanded_size(evar, envp);
}

void	substitute_var(t_evar *evar, t_list *envp)
{
	if (copy_exitsig_value(evar))
		return ;
	evar->dol_expansion_variable
		= (char *)malloc(sizeof(char) * (evar->size_expanded_var + 1));
	if (!evar->dol_expansion_variable)
		return (malloc_error_dol(evar));
	ft_memcpy(evar->dol_expansion_variable,
		evar->newvalue_copy - evar->size_expanded_var + evar->id_copy,
		evar->size_expanded_var);
	evar->dol_expansion_variable[evar->size_expanded_var] = '\0';
	evar->dol_expansion_value = get_envvar_value(&envp,
			evar->dol_expansion_variable);
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

void	expand_dol(t_evar *evar, int inside, t_list *envp)
{
	evar->size_expanded_var = 0;
	evar->id_copy++;
	if (current_char(evar) == '{')
	{
		evar->id_copy++;
		if (current_char(evar) == '?')
			return (trigger_exitsig_copy_handler(evar, envp));
		while (current_char(evar) != '}')
			increase_expanded_var_size_and_index(evar);
	}
	else if (current_char(evar) != '{')
	{
		while (valid_identifier_char(current_char(evar)))
			increase_expanded_var_size_and_index(evar);
		if (current_char(evar) == '?')
			return (trigger_exitsig_copy_handler(evar, envp));
		if (copy_single_dollar(evar, inside))
			return ;
	}
	substitute_var(evar, envp);
}
