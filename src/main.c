/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pantoine <pantoine@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 02:28:18 by lefabreg          #+#    #+#             */
/*   Updated: 2024/05/14 14:51:55 by pantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/evars.h"
#include "../includes/execute.h"

int	g_current_sig = 0;

int	mainloop(t_shell *shell)
{
	char	*command;

	while (1)
	{
		handle_signals();
		command = readline("Super prompt > ");
		if (!ft_strncmp(command, "\n", 1))
		{
			free(command);
			continue ;
		}
		if (!ft_strncmp(command, "exit", 4) && ft_strlen(command) == 4)
		{
			write(1, "exit\n", 5);
			free(command);
			break ;
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
	export_envar(&shell, "T=test");
	export_envar(&shell, "T+=test");
	export_envar(&shell, "T+=test");
	unset_envvar(&shell, "T");
	//show_me_the_way(shell.envp);
	//efftee_echo(&shell, "\"     \"-n '   'bonjour a tous$SHLVL''\"$AHA\"");
	//efftee_echo(&shell, "'   'bonjour a tous$SHLVL''\"$AHA\"");
	mainloop(&shell);
	//export_envar(&shell, "HOME\"=\"'   yooo''''...${HOME}...$?'${UNL_UCKY}?PANTOINE/${SHLVL}");
	//efftee_echo(&shell, "''$TEST bonjour  a tous, NO NEWLINE$SHLVL''\"$AHA\"");
	//unset_envvar(&shell, "PATHe HOME ${ABC} ahahahahah");
	free_envp(shell.envp);
	return (0);
}
