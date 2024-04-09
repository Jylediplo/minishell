/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pantoine <pantoine@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 14:44:56 by pantoine          #+#    #+#             */
/*   Updated: 2024/04/09 12:20:22 by pantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
// readline
# include <readline/readline.h>
// history
# include <readline/history.h>
// signal
# include <signal.h>
// basic i/o
# include <unistd.h>
# include <fcntl.h>
# include <termcap.h>
# include <termios.h>
# include <sys/wait.h>
//# include <term.h>
// libft
# include "../libft/libft.h"

/// functions prototype
// signals
extern int	g_current_sig;
void		handle_signals(void);

// history
// typedef struct s_history
// {
// 	int		nb;
// 	char	*line;
// }			t_history;
//
// void		manage_history(char *command, t_list **list);
// void		ft_lst_display(t_list *lst);
void		free_history_data(void *data);

#endif
