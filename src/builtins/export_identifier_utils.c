/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_identifier_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pantoine <pantoine@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 12:15:55 by pantoine          #+#    #+#             */
/*   Updated: 2024/04/26 17:01:30 by pantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/evars.h"

void	add_space_next_arg(t_evar *evar)
{
	while (is_whitespace(evar->newvalue_copy[evar->id_copy]))
		evar->id_copy++;
	if (!evar->newvalue_copy[evar->id_copy])
		return ;
	evar->newvalue_toset[evar->id_toset++] = ' ';
}

void	goto_next_arg(t_evar *evar)
{
	while (is_whitespace(*evar->newvalue))
		evar->newvalue++;
	if (!*evar->newvalue)
		return ;
	evar->size_evar++;
}
