/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_signals.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lefabreg <lefabreg@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 02:58:42 by lefabreg          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/05/17 13:09:01 by lefabreg         ###   ########lyon.fr   */
=======
/*   Updated: 2024/05/30 17:56:06 by pantoine         ###   ########.fr       */
>>>>>>> execute
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	handler_heredoc(int sig, siginfo_t *siginfo, void *unused)
{
	(void)siginfo;
	(void)unused;
	g_current_sig = 128 + sig;
	if (sig == SIGINT)
		printf("\n");
}

void	handler(int sig, siginfo_t *siginfo, void *unused)
{
	(void)siginfo;
	(void)unused;
	g_current_sig = 128 + sig;
	if (sig == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else if (sig == SIGQUIT)
	{
		g_current_sig = 0;
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	if (sig == SIGQUIT)
	{
		write(2, "Quit (core dumped)\n", 19);
		exit(131);
	}
}

void	handle_signals(t_shell *shell)
{
	struct sigaction	catch;

	signal(SIGQUIT, SIG_IGN);
	sigemptyset(&catch.sa_mask);
	catch.sa_flags = SA_SIGINFO;
	catch.sa_sigaction = handler;
	shell->catcher = catch;
	if ((sigaction(SIGUSR1, &catch, 0)) == -1)
		return ;
	if ((sigaction(SIGUSR2, &catch, 0)) == -1)
		return ;
	if ((sigaction(SIGINT, &catch, 0)) == -1)
		return ;
	if ((sigaction(SIGQUIT, &catch, 0)) == -1)
		return ;
}
