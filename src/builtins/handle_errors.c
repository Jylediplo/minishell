/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pantoine <pantoine@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 15:02:50 by pantoine          #+#    #+#             */
/*   Updated: 2024/04/19 21:26:50 by pantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/evars.h"

void	evar_error_message(t_evar *evar)
{
	if (evar->error == MALLOC)
	{
		printf("error !!\n");
		ft_putstr_fd("error: malloc failure\n", 2);
	}
	else if (evar->error == BAD_SUBSTITUTION)
	{
		printf("error !!\n");
		ft_putstr_fd("error: bad substitution\n", 2);
	}
	else if (evar->error == UNCLOSED_QUOTE)
	{
		printf("error !!\n");
		ft_putstr_fd("error: unclosed quote detected\n", 2);
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

