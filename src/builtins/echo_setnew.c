/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_setnew.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pantoine <pantoine@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 11:04:06 by pantoine          #+#    #+#             */
/*   Updated: 2024/05/14 23:17:08 by pantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/evars.h"

void	copy_quoted_sequence_echo(t_evar *evar, char quotetype, t_list *envp)
{
	while (current_char(evar) != quotetype)
	{
		if (current_char(evar) == '$')
			expand_dol(evar, 0, envp);
		else
			copy_char(evar);
		if (evar->e_error == MALLOC)
			return ;
	}
	evar->id_copy++;
	while (current_char(evar) != quotetype)
	{
		if (current_char(evar) == '$' && quotetype == '\"')
			expand_dol(evar, 1, envp);
		else
			copy_char(evar);
		if (evar->e_error == MALLOC)
			return ;
	}
	if (current_char(evar))
		evar->id_copy++;
}

void	get_echo(t_evar *evar, t_list *envp)
{
	find_next_quotes(evar, evar->newvalue_copy, evar->id_copy);
	while (current_char(evar))
	{
		get_next_quotetype(evar);
		if (evar->quotetype)
			copy_quoted_sequence_echo(evar, evar->quotetype, envp);
		else if (!evar->double_qchar && !evar->single_qchar)
		{
			if (current_char(evar) == '$')
				expand_dol(evar, 0, envp);
			else
				copy_char(evar);
		}
		if (evar->e_error == STOP || evar->e_error == MALLOC)
			return ;
		find_next_quotes(evar, evar->newvalue_copy, evar->id_copy);
	}
	evar->newvalue_toset[evar->id_toset] = '\0';
}
