/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pantoine <pantoine@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 02:28:18 by lefabreg          #+#    #+#             */
/*   Updated: 2024/04/09 12:20:17 by pantoine         ###   ########.fr       */
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
		printf("Getent value: %s\n", term_buff);
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
			execve("./minishell", ft_split("./minishell", ' '), envp);
		else
			wait(NULL);
	}
}

int	mainloop(int argc, char **argv, char **envp)
{
	char	*command;

	(void)argc;
	(void)argv;
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
		handle_minishell_cmd(command, envp);
		free(command);
	}
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	char	*path;

	path = ttyname(0);
	(void)argv;
	(void)argc;
	printf("%s\n", path);
	create_term(envp);
	mainloop(argc, argv, envp);
	return (0);
}
