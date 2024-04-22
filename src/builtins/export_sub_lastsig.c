/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_sub_lastsig.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pantoine <pantoine@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 18:22:46 by pantoine          #+#    #+#             */
/*   Updated: 2024/04/22 18:29:39 by pantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/evars.h"

int	get_exitsig_size(t_evar *evar)
{
	char	*sigvalue;

	if (evar->size_expanded_var != 1
		&& *(evar->newvalue - evar->size_expanded_var) != '?')
		return (0);
	sigvalue = ft_itoa(g_current_sig);
	if (!sigvalue)
	{
		set_err_status(evar, MALLOC);
		return (1);
	}
	evar->size_evar += ft_strlen(sigvalue);
	free(sigvalue);
	if (*evar->newvalue == '}')
		evar->newvalue++;
	return (1);
}

int	copy_exitsig_value(t_evar *evar)
{
	char	*sigvalue;

	if (evar->size_expanded_var != 1
		&& evar->newvalue_copy[evar->id_copy - evar->size_expanded_var] != '?')
		return (0);
	sigvalue = ft_itoa(g_current_sig);
	if (!sigvalue)
	{
		set_err_status(evar, MALLOC);
		return (1);
	}
	ft_memcpy(evar->newvalue_toset + evar->id_toset,
		sigvalue,
		ft_strlen(sigvalue));
	evar->id_toset += ft_strlen(sigvalue);
	if (current_char(evar) == '}')
		evar->id_copy++;
	free(sigvalue);
	return (1);
}

void	trigger_exitsig_copy_handler(t_evar *evar)
{
	increase_expanded_var_size_and_index(evar);
	substitute_var(evar);
}

void	trigger_exitsig_size_handler(t_evar *evar)
{
	increase_expanded_var_size(evar);
	get_expanded_size(evar);
}
