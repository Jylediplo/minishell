/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pantoine <pantoine@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 02:28:18 by lefabreg          #+#    #+#             */
/*   Updated: 2024/05/12 17:39:42 by pantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/evars.h"
#include "../includes/execute.h"

int	g_current_sig = 0;

void	handle_minishell_cmd(char *command, char **envp)
{
	pid_t	id;

	if (!ft_strncmp(command, "./minishell", 11) && ft_strlen(command) == 11)
	{
		id = fork();
		if (!id)
		{
			if (execve(command, ft_split(command, ' '), envp) == -1)
				perror("minishell");
		}
		else
			wait(NULL);
	}
}

int	mainloop(t_shell *shell)
{
	char	*command;

	(void)shell;
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
		handle_minishell_cmd(command, /*shell->envp*/NULL);
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
	export_envar(&shell, "HOME\"=\"'   yooo''''...${HOME}...$?'${UNL_UCKY}?PANTOINE/${SHLVL}");
	efftee_echo(&shell, "\"     \"-n '   'bonjour a tous$SHLVL''\"$AHA\"");
	efftee_echo(&shell, "''$TEST bonjour  a tous, NO NEWLINE$SHLVL''\"$AHA\"");
	unset_envvar(&shell, "PATHe HOME ${ABC} ahahahahah");
	free_envp(shell.envp);
	return (0);
}
