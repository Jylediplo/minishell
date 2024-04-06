/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_signals.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lefabreg <lefabreg@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 02:58:42 by lefabreg          #+#    #+#             */
/*   Updated: 2024/04/06 03:09:45 by lefabreg         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char tab[2][10] = {"EXPORT", "exit"};

void	handler(int sig, siginfo_t *siginfo, void *unused)
{
    (void)siginfo;
	(void)unused;
    
	if (sig == SIGINT)
    {
        printf("process killed\n");
        exit(1);
    }
}

void    handle_signals(void)
{
    struct sigaction    catch;
    
	sigemptyset(&catch.sa_mask);
	catch.sa_flags = SA_SIGINFO;
	catch.sa_sigaction = handler;
	if ((sigaction(SIGUSR1, &catch, 0)) == -1)
		return ;
	if ((sigaction(SIGUSR2, &catch, 0)) == -1)
		return ;
	if ((sigaction(SIGINT, &catch, 0)) == -1)
		return ;
}