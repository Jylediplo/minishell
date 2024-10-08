/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_substitutions_utils.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pantoine <pantoine@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 11:11:40 by pantoine          #+#    #+#             */
/*   Updated: 2024/05/19 12:25:17 by pantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/evars.h"

int	count_single_dollar(t_evar *evar, int inside)
{
	if (!evar->size_expanded_var && (inside || !evar->quotetype))
	{
		evar->size_evar++;
		return (1);
	}
	return (0);
}

int	copy_single_dollar(t_evar *evar, int inside)
{
	if (!evar->size_expanded_var && (inside || !evar->quotetype))
	{
		evar->id_copy--;
		copy_char(evar);
		return (1);
	}
	return (0);
}
