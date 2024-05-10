/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_errors.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pantoine <pantoine@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 18:06:02 by pantoine          #+#    #+#             */
/*   Updated: 2024/05/10 22:00:48 by pantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execute.h"

void	malloc_exec_err(void)
{
	ft_putstr_fd("petitcoq: malloc error\n", 2);
}

void	unexpected_token_exec_err(char *error_token)
{
	ft_putstr_fd("petitcoq: syntax error near unexpected token `", 2);
	ft_putstr_fd(error_token, 2);
	ft_putstr_fd("'\n", 2);
}
