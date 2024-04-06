/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pantoine <pantoine@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 02:28:18 by lefabreg          #+#    #+#             */
/*   Updated: 2024/04/06 17:12:43 by pantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	current_sig = 0;

int  main(void)
{
    char	*command;

    while (1)
    {
        handle_signals();
        command = readline("Super prompt > ");
		if (!ft_strncmp(command, "\n", 1))
			continue ;
		if (!ft_strncmp(command, "exit", 4) && ft_strlen(command) == 4)
		{
			write(1, "exit\n", 5);
			free(command);
			break ;
		}
        free(command);
    }
    return (0);
}
