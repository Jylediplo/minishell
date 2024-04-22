/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pantoine <pantoine@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 11:05:06 by pantoine          #+#    #+#             */
/*   Updated: 2024/04/22 18:57:15 by pantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/evars.h"

int	allowed_in_substitution(char c)
{
	if ((c >= 48 && c <= 57)
		|| (c >= 65 && c <= 90)
		|| (c == 95)
		|| (c >= 97 && c <= 122))
		return (1);
	return (0);
}

int	allowed_in_braces(char c)
{
	if (c != '\''
		&& c != '\"'
		&& c != '{'
		&& !is_whitespace(c))
		return (1);
	return (0);
}

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
