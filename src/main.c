/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pantoine <pantoine@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 02:28:18 by lefabreg          #+#    #+#             */
/*   Updated: 2024/04/08 18:56:57 by pantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	g_current_sig = 0;

void	create_term(char **envp)
{
	char	*termtype;
	char	term_buff[2048];
	int		status;
	// char	*clear;


	(void)envp;
	termtype = getenv("TERM");
	if (!termtype)
		printf("terminal type not found\n");
	status = tgetent(term_buff, termtype);
	if (!status)
		printf("Terminal type not defined\n");
	else if (status < 0)
		printf("Could not access termcap database\n");	
	// else
	// 	printf("Getent value: %s\n", term_buff);
	// clear = tgetstr("cl", NULL);
    // if (clear != NULL) {
    //     tputs(clear, 1, putchar);
    // }


    if (!isatty(STDOUT_FILENO)) {
        fprintf(stderr, "STDOUT is not a terminal\n");
        exit(EXIT_FAILURE);
    }
 struct termios old_termios;

    if (tcgetattr(STDOUT_FILENO, &old_termios) == -1) {
        perror("tcgetattr");
        exit(EXIT_FAILURE);
    }

    struct termios new_termios = old_termios;
    //new_termios.c_lflag &= ~(ICANON);
    if (tcsetattr(STDOUT_FILENO, TCSANOW, &new_termios) == -1) {
        perror("tcsetattr");
        exit(EXIT_FAILURE);
    }


    printf("New terminal initialized\n");
	// if (tcsetattr(STDOUT_FILENO, TCSANOW, &old_termios) == -1) {
    //     perror("tcsetattr");
    //     exit(EXIT_FAILURE);
    // }

}

int	main(int argc, char **argv, char **envp)
{
	t_list	*list;
	char	*command;
	pid_t id;

	list = NULL;
	(void)argc;
	(void)argv;
	char *path = ttyname(0);
	printf("%s\n", path);
	create_term(envp);
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
			ft_lstclear(&list, free_history_data);
			free(command);
			break ;
		}
		manage_history(command, &list);
		if (!ft_strncmp(command, "history", 7) && ft_strlen(command) == 7)
			ft_lst_display(list);
		if (!ft_strncmp(command, "./minishell", 11) && ft_strlen(command) == 11)
		{
			id = fork();
			if (!id)
				execve("./minishell", ft_split("./minishell", ' '), envp);
			else
				wait(NULL);
		}
		free(command);
	}
	return (0);
}
