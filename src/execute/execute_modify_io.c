/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_modify_io.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pantoine <pantoine@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 10:55:30 by pantoine          #+#    #+#             */
/*   Updated: 2024/05/30 13:24:43 by pantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/execute.h"

static int	get_term_fd(void)
{
	int	terminal_fd;

	terminal_fd = -1;
	if (isatty(STDIN_FILENO))
		terminal_fd = STDIN_FILENO;
	else if (isatty(STDOUT_FILENO))
		terminal_fd = STDOUT_FILENO;
	else if (isatty(STDERR_FILENO))
		terminal_fd = STDERR_FILENO;
	else
		return (-1);
	return (terminal_fd);
}

int	reset_termsettings(struct termios *term_og)
{
	int	terminal_fd;

	terminal_fd = get_term_fd();
	if (terminal_fd == -1)
		return (1);
	tcsetattr(terminal_fd, TCSANOW, term_og);
	return (0);
}

int	get_og_termsettings(struct termios *term_og)
{
	int	terminal_fd;

	terminal_fd = get_term_fd();
	if (terminal_fd == -1)
		return (1);
	if (tcgetattr(terminal_fd, term_og))
		return (1);
	return (0);
}

static int	terminal_init(void)
{
	int				terminal_fd;
	struct termios	term_settings;

	terminal_fd = get_term_fd();
	if (terminal_fd == -1)
		return (1);
	if (tcgetattr(terminal_fd, &term_settings))
		return (1);
	term_settings.c_lflag |= NOFLSH;
	tcsetattr(terminal_fd, TCSANOW, &term_settings);
	return (0);
}

int	modify_termio(t_shell *shell)
{
	//change the signal handler
	
	shell->catcher.sa_sigaction = handler_heredoc;
	//shell->catcher.sa_flags = SA_RESTART;
	if ((sigaction(SIGINT, &shell->catcher, 0)) == -1)
		return (1);
	if ((sigaction(SIGQUIT, &shell->catcher, 0)) == -1)
		return (1);
	if (terminal_init())
		return (1);
	return (0);
}
