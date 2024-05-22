/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pantoine <pantoine@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 15:02:50 by pantoine          #+#    #+#             */
/*   Updated: 2024/05/22 19:13:31 by pantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/evars.h"

void	evar_error_message(t_evar *evar, char *context)
{
	if (evar->e_error == MALLOC)
	{
		ft_putstr_fd("petitcoq: malloc: failure\n", 2);
		g_current_sig = 1;
	}
	else if (evar->e_error == BAD_SUBSTITUTION)
	{
		ft_putstr_fd("petitcoq: error: bad substitution\n", 2);
		g_current_sig = 1;
	}
	else if (evar->e_error == UNCLOSED_QUOTE)
		ft_putstr_fd("petitcoq: error: unclosed quote detected\n", 2);
	else if (evar->e_error == UNCLOSED_BRACE)
		ft_putstr_fd("petitcoq: error: unclosed brace detected\n", 2);
	else if (evar->e_error == INVALID_IDENTIFIER)
	{
		ft_putstr_fd("petitcoq: error: not a valid identifier `", 2);
		ft_putstr_fd(context, 2);
		ft_putstr_fd("'\n", 2);
		g_current_sig = 1;
	}
}

void	malloc_error_dol(t_evar *evar)
{
	set_err_status(evar, MALLOC);
	free(evar->newvalue_copy);
	free(evar->newvalue_toset);
	evar->newvalue_copy = NULL;
	evar->newvalue_toset = NULL;
}

void	set_err_status(t_evar *evar, int status)
{
	evar->e_error = status;
}
