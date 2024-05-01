/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pantoine <pantoine@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 20:27:44 by pantoine          #+#    #+#             */
/*   Updated: 2024/04/30 21:21:43 by pantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/evars.h"

int	efftee_echo(t_shell *shell, char *to_echo)
{
	char	*echo_value;

	echo_value = parse_echo(shell->envp, to_echo);
	if (!echo_value)
		return (1);
	return (0);
}
