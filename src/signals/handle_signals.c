/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_signals.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyjy <jyjy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 02:58:42 by lefabreg          #+#    #+#             */
/*   Updated: 2024/05/31 18:28:08 by pantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/execute.h"

void	handler_heredoc(int sig)
{
	g_current_sig = 128 + sig;
	if (sig == SIGINT)
	{
		printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
	}
}

void	ignore_sigint(void)
{
	struct sigaction	sig;

	sigemptyset(&sig.sa_mask);
	sig.sa_handler = SIG_IGN;
	sig.sa_flags = 0;
	sigaction(SIGINT, &sig, 0);
	sigaction(SIGQUIT, &sig, 0);
}

void	handler_exec(int sig)
{
	g_current_sig = 128 + sig;
	if (sig == SIGQUIT)
	{
		printf("Quit (core dumped)\n");
		rl_on_new_line();
		rl_replace_line("", 0);
	}
}

void	handler_foreground(int sig)
{
	g_current_sig = 128 + sig;
	if (sig == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	handle_signals(e_sig_mode mode)
{
	struct sigaction	sig;

	sigemptyset(&sig.sa_mask);
	sig.sa_handler = SIG_IGN;
	sig.sa_flags = 0;
	sigaction(SIGINT, &sig, 0);
	sigaction(SIGQUIT, &sig, 0);
	if (mode == SIG_FG)
	{
		sig.sa_handler = &handler_foreground;
		sigaction(SIGINT, &sig, 0);
	}
	else if (mode == SIG_HD)
	{
		sig.sa_handler = &handler_heredoc;
		sigaction(SIGINT, &sig, 0);
	}
	else if (mode == SIG_EXEC)
	{
		sig.sa_handler = &handler_exec;
		sigaction(SIGINT, &sig, 0);
		sigaction(SIGQUIT, &sig, 0);
	}
}
