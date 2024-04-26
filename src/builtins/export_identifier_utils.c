/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_identifier_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pantoine <pantoine@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 12:15:55 by pantoine          #+#    #+#             */
/*   Updated: 2024/04/26 14:13:08 by pantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/evars.h"

char	*save_next_evar(t_evar *evar)
{
	while (is_whitespace(*evar->newvalue))
		evar->newvalue++;
	if (!*evar->newvalue)
	{
		evar->set_next = NULL;
		set_err_status(evar, STOP);
		return (NULL);
	}
	evar->set_next = evar->newvalue;
	set_err_status(evar, STOP);
	return (NULL);
}
