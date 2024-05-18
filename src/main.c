/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pantoine <pantoine@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 02:28:18 by lefabreg          #+#    #+#             */
/*   Updated: 2024/05/18 20:33:10 by pantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/evars.h"
#include "../includes/execute.h"

unsigned char	g_current_sig = 0;

int	mainloop(t_shell *shell)
{
	char	*command;

	while (1)
	{
		handle_signals();
		command = readline("Super prompt > ");
		if (!command)
		{
			printf("unlucky\n");
			break ;
		}
		if (!ft_strncmp(command, "\n", 1))
		{
			free(command);
			continue ;
		}
		split_word(command, shell);
		free(command);
	}
	return (0);
}

void	init_shell(int argc, char **argv, char **envp, t_shell *shell)
{
	shell->argc = argc;
	shell->argv = argv;
	shell->envp = copy_env(envp);
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;

	init_shell(argc, argv, envp, &shell);
	mainloop(&shell);
	free_envp(shell.envp);
	return (0);
}
