/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pantoine <pantoine@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 11:05:06 by pantoine          #+#    #+#             */
/*   Updated: 2024/04/28 11:16:34 by pantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/evars.h"

void	increase_expanded_var_size(t_evar *evar)
{
	evar->size_expanded_var++;
	evar->newvalue++;
}

void	increase_expanded_var_size_and_index(t_evar *evar)
{
	evar->id_copy++;
	evar->size_expanded_var++;
}

void	increase_size_evar(t_evar *evar)
{
	evar->newvalue++;
	evar->size_evar++;
}
