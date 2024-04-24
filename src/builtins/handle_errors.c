/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pantoine <pantoine@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 15:02:50 by pantoine          #+#    #+#             */
/*   Updated: 2024/04/24 16:50:36 by pantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/evars.h"

void	evar_error_message(t_evar *evar)
{
	if (evar->error == MALLOC)
		ft_putstr_fd("error: malloc failure\n", 2);
	else if (evar->error == BAD_SUBSTITUTION)
		ft_putstr_fd("error: bad substitution\n", 2);
	else if (evar->error == UNCLOSED_QUOTE)
		ft_putstr_fd("error: unclosed quote detected\n", 2);
	else if (evar->error == INVALID_IDENTIFIER)
		ft_putstr_fd("error: not a valid identifier\n", 2);
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
	evar->error = status;
}
