/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pantoine <pantoine@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 02:28:18 by lefabreg          #+#    #+#             */
/*   Updated: 2024/04/06 04:07:53 by pantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int  main(void)
{
    char				*command;
    struct sigaction    catch;

    while (1)
    {
        command = readline("Super prompt > ");
        printf("command : %s \n", command);
        handle_signals(&catch);
		if (catch.sa_sigaction.si_signo == 2)
		{
			free(command);
			break ;
		}
        free(command);
    }
    return (0);
}
