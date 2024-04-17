/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pantoine <pantoine@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 15:02:50 by pantoine          #+#    #+#             */
/*   Updated: 2024/04/17 16:05:56 by pantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	evar_error_message(t_evar *evar)
{
	if (evar->error == MALLOC)
		ft_putstr_fd("error: malloc failure\n", 2);
	else if (evar->error == BAD_SUBSTITUTION)
		ft_putstr_fd("error: bad substitution\n", 2);
	else if (evar->error == UNCLOSED_QUOTE)
		ft_putstr_fd("error: unclosed quote detected\n", 2);
}
