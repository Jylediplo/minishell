/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_getsize.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pantoine <pantoine@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 11:03:48 by pantoine          #+#    #+#             */
/*   Updated: 2024/05/13 18:05:42 by pantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/evars.h"

void	init_evar(t_evar *evar, char *newvalue)
{
	evar->size_evar = 0;
	evar->id_toset = 0;
	evar->id_copy = 0;
	find_next_quotes(evar, newvalue, 0);
	evar->newvalue = newvalue;
	evar->newvalue_toset = NULL;
	evar->error = NONE;
	evar->set_next = NULL;
}

char	*parse_quoted_sequence(t_evar *evar, char quotetype, t_list *envp)
{
	if (!ft_strchr(evar->newvalue + 1, quotetype))
		return (set_err_status(evar, UNCLOSED_QUOTE), NULL);
	while (*evar->newvalue != quotetype && evar->error != BAD_SUBSTITUTION)
	{
		if (*evar->newvalue == '$')
			size_dol_substitution(evar, 0, envp);/*
		else if (is_whitespace(*evar->newvalue))
			return (save_next_evar(evar));*/
		else
			increase_size_evar(evar);
	}
	evar->newvalue++;
	while (*evar->newvalue != quotetype
		&& evar->error != BAD_SUBSTITUTION
		&& evar->error != MALLOC)
	{
		if (*evar->newvalue == '$' && quotetype == '\"')
			size_dol_substitution(evar, 1, envp);
		else
			increase_size_evar(evar);
	}
	if (*evar->newvalue)
		evar->newvalue += 1;
	return (evar->newvalue);
}

void	get_next_quotetype(t_evar *evar)
{
	if ((!evar->double_qchar && evar->single_qchar)
		|| (evar->double_qchar > evar->single_qchar && evar->single_qchar))
	{
		evar->quotetype = '\'';
		return ;
	}
	else if ((evar->double_qchar && !evar->single_qchar)
		|| (evar->double_qchar < evar->single_qchar && evar->double_qchar))
	{
		evar->quotetype = '\"';
		return ;
	}
	evar->quotetype = '\0';
	return ;
}

void	get_evar_size(t_evar *evar, t_list *envp)
{
	while (*evar->newvalue)
	{
		get_next_quotetype(evar);
		if (evar->quotetype)
			evar->newvalue = parse_quoted_sequence(evar, evar->quotetype, envp);
		else if (!evar->quotetype)
		{
			if (*evar->newvalue == '$')
				size_dol_substitution(evar, 0, envp);/*
			else if (is_whitespace(*evar->newvalue))
			{
				save_next_evar(evar);
				return (set_err_status(evar, STOP));
			}*/
			else
				increase_size_evar(evar);
		}
		if (evar->error == BAD_SUBSTITUTION
			|| evar->error == MALLOC
			|| !evar->newvalue)
			return ;
		find_next_quotes(evar, evar->newvalue, 0);
	}
}

char	*parse_evar(t_evar *evar, char *newvalue, t_list *envp)
{
	init_evar(evar, newvalue);
	get_evar_size(evar, envp);
	if (evar->error != NONE && evar->error != STOP)
	{
		evar_error_message(evar);
		return (NULL);
	}
	evar->error = NONE;
	evar->newvalue_copy = ft_strdup(newvalue);
	evar->newvalue_toset = (char *)malloc(sizeof(char) * (evar->size_evar + 1));
	if (!evar->newvalue_toset)
		return (NULL);
	get_evar(evar, envp);
	if (evar->error == MALLOC)
		ft_putstr_fd("Malloc error, can't display string\n", 2);
	free(evar->newvalue_copy);
	return (evar->newvalue_toset);
}
