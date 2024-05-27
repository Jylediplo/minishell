/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_signals.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lefabreg <lefabreg@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 02:58:42 by lefabreg          #+#    #+#             */
/*   Updated: 2024/05/27 11:32:24 by pantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	handler(int sig, siginfo_t *siginfo, void *unused)
{
	(void)siginfo;
	(void)unused;
	g_current_sig = 128 + sig;
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else if (sig == SIGQUIT)
	{
		g_current_sig = 0;
		write(1, "\0", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	handle_signals(void)
{
	struct sigaction	catch;

	sigemptyset(&catch.sa_mask);
	catch.sa_flags = SA_SIGINFO;
	catch.sa_sigaction = handler;
	if ((sigaction(SIGUSR1, &catch, 0)) == -1)
		return ;
	if ((sigaction(SIGUSR2, &catch, 0)) == -1)
		return ;
	if ((sigaction(SIGINT, &catch, 0)) == -1)
		return ;
	if ((sigaction(SIGQUIT, &catch, 0)) == -1)
		return ;
}
