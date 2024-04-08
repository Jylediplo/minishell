/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pantoine <pantoine@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 02:28:18 by lefabreg          #+#    #+#             */
/*   Updated: 2024/04/08 17:08:53 by pantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	g_current_sig = 0;

void	create_term(void)
{
	char	*termtype;
	char	term_buff[2048];
	int		status;

	termtype = getenv("TERM");
	if (!termtype)
		printf("terminal type not found\n");
	status = tgetent(term_buff, termtype);
	if (!status)
		printf("Terminal type not defined\n");
	else if (status < 0)
		printf("Could not access termcap database");	
	else
		printf("Getent value: %s\n", term_buff);
	tputs(tgetstr("cl", NULL), 1, putchar);
}

int	main(void)
{
	t_list	*list;
	char	*command;

	list = NULL;
	create_term();
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
		free(command);
	}
	return (0);
}
