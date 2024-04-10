/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pantoine <pantoine@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 02:28:18 by lefabreg          #+#    #+#             */
/*   Updated: 2024/04/10 23:29:09 by pantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	g_current_sig = 0;

void	create_term(char **envp)
{
	char	*termtype;
	char	term_buff[2048];
	int		status;
	char	*clear;

	(void)envp;
	termtype = getenv("TERM");
	if (!termtype)
		printf("terminal type not found\n");
	status = tgetent(term_buff, termtype);
	if (!status)
		printf("Terminal type not defined\n");
	else if (status < 0)
		printf("Could not access termcap database\n");
	else
		printf("success\n");
	clear = tgetstr("cl", NULL);
	if (clear != NULL)
		tputs(clear, 1, putchar);
}

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
		handle_minishell_cmd(command, shell->envp);
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
	int		i;

	i = 0;
	init_shell(argc, argv, envp, &shell);
	create_term(shell.envp);
	//mainloop(&shell);
	parse_evar(&shell, "\"hel\'l\'o world\"...wh\'a\'tsup?");	
	i = 0;
	while (shell.envp[i])
		free(shell.envp[i++]);
	free(shell.envp);
	return (0);
}
