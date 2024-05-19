/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_sub_lastsig_utils.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pantoine <pantoine@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 19:43:40 by pantoine          #+#    #+#             */
/*   Updated: 2024/05/19 12:28:37 by pantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/evars.h"

static int	is_legal_sigsub_copy(t_evar *evar)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (evar->newvalue_copy[evar->id_copy - evar->size_expanded_var + i++]
		== '?')
		count++;
	if (count > 1)
	{
		while (evar->newvalue_copy[evar->id_copy] != '}')
			evar->id_copy++;
		return (1);
	}
	while (evar->newvalue_copy[evar->id_copy] != '}')
	{
		if (!valid_identifier_char(evar->newvalue_copy[evar->id_copy++]))
		{
			set_err_status(evar, BAD_SUBSTITUTION);
			return (0);
		}
	}
	return (1);
}

static int	is_legal_sigsub_count(t_evar *evar)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (*(evar->newvalue - evar->size_expanded_var + i++) == '?')
		count++;
	if (count > 1)
	{
		while (*evar->newvalue != '}')
			evar->newvalue++;
		return (1);
	}
	while (*evar->newvalue != '}')
	{
		if (!valid_identifier_char(*evar->newvalue++))
		{
			set_err_status(evar, BAD_SUBSTITUTION);
			return (0);
		}
	}
	return (1);
}

int	handle_questionmarks_in_braces_copy(t_evar *evar)
{
	if (evar->newvalue_copy[evar->id_copy - evar->size_expanded_var - 1]
		== '{')
	{
		if (!is_legal_sigsub_copy(evar))
			return (0);
	}
	return (1);
}

int	handle_questionmarks_in_braces_size(t_evar *evar)
{
	if (*(evar->newvalue - evar->size_expanded_var - 1) == '{')
	{
		if (!is_legal_sigsub_count(evar))
			return (0);
	}
	return (1);
}
