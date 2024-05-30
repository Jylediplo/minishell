/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pantoine <pantoine@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 02:28:18 by lefabreg          #+#    #+#             */
/*   Updated: 2024/05/29 18:35:06 by pantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/evars.h"
#include "../includes/execute.h"

unsigned char	g_current_sig = 0;

static int	mainloop(t_shell *shell)
{
	char	*command;

	while (1)
	{
		handle_signals(shell);
		command = readline("Super prompt > ");
		if (!command)
			return (g_current_sig);
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
	printf("exit\n");
	return (retval);
}
