/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_setnew.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pantoine <pantoine@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 11:04:06 by pantoine          #+#    #+#             */
/*   Updated: 2024/05/02 13:52:58 by pantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/evars.h"

void	copy_char(t_evar *evar)
{
	evar->newvalue_toset[evar->id_toset++]
		= evar->newvalue_copy[evar->id_copy++];
}

char	current_char(t_evar *evar)
{
	return (evar->newvalue_copy[evar->id_copy]);
}

void	copy_quoted_sequence(t_evar *evar, char quotetype, t_list *envp)
{
	while (current_char(evar) != quotetype)
	{
		if (current_char(evar) == '$')
			expand_dol(evar, 0, envp);
		else if (is_whitespace(current_char(evar)))
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
			expand_dol(evar, 1, envp);
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

void	get_evar(t_evar *evar, t_list *envp)
{
	find_next_quotes(evar, evar->newvalue_copy, evar->id_copy);
	while (current_char(evar))
	{
		get_next_quotetype(evar);
		if (evar->quotetype)
			copy_quoted_sequence(evar, evar->quotetype, envp);
		else if (!evar->double_qchar && !evar->single_qchar)
		{
			if (current_char(evar) == '$')
				expand_dol(evar, 0, envp);
			else if (is_whitespace(current_char(evar)))
				break ;
			else
				copy_char(evar);
		}
		if (evar->error == STOP || evar->error == MALLOC)
		{
			evar->newvalue_toset[evar->id_toset] = '\0';
			return ;
		}
		find_next_quotes(evar, evar->newvalue_copy, evar->id_copy);
	}
	evar->newvalue_toset[evar->id_toset] = '\0';
}
