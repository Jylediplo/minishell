/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pantoine <pantoine@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 02:28:18 by lefabreg          #+#    #+#             */
/*   Updated: 2024/06/03 11:41:15 by pantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/evars.h"
#include "../includes/execute.h"

unsigned char	g_current_sig = 0;

static int	mainloop(t_shell *shell)
{
	char		*command;

	shell->history.list = NULL;
	restore_history(&shell->history);
	while (1)
	{
		handle_signals(SIG_FG);
		command = readline(ONE TWO THREE FOUR FIVE \
					SIX SEVEN EIGHT NINE TEN EL TW THIR FOURT FIFT END);
		if (!command)
			return (g_current_sig);
		add_to_history(command, &shell->history);
		if (!is_same_str(command, "\0"))
			split_word(command, shell);
		free(command);
	}
	return (0);
}

static void	init_shell(int argc, char **argv, char **envp, t_shell *shell)
{
	shell->argc = argc;
	shell->argv = argv;
	shell->envp = copy_env(envp);
	shell->children = NULL;
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;
	int		retval;

	init_shell(argc, argv, envp, &shell);
	retval = mainloop(&shell);
	free_envp(shell.envp);
	ft_lstclear(&shell.history.list, free_history_data);
	printf("exit\n");
	return (retval);
}
