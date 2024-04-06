/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pantoine <pantoine@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 02:28:18 by lefabreg          #+#    #+#             */
/*   Updated: 2024/04/06 15:08:14 by pantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	current_sig = 0;

int  main(void)
{
    char	*command;

    while (1)
    {
        command = readline("Super prompt > ");
        handle_signals();
		if (current_sig == 2)
		{
			printf("The programme will now exit.\n");
			free(command);
			break ;
		}
        free(command);
    }
    return (0);
}
