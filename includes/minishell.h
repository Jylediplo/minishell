/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pantoine <pantoine@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 14:44:56 by pantoine          #+#    #+#             */
/*   Updated: 2024/05/09 18:47:52 by pantoine         ###   ########.fr       */
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
// libft
# include "../libft/libft.h"

# ifndef T_SHELL
#  define T_SHELL
typedef struct  s_shell
{
    int     argc;
    char    **argv;
    t_list	*envp;
}   t_shell;
# endif

/// functions prototype
// signals
extern int	g_current_sig;
void		handle_signals(void);

void		free_history_data(void *data);

// env variables and export functions
t_list  *copy_env(char **envp);
void	free_envp(t_list *envp);
int    	export_envar(t_shell *shell, char *to_change);
char	*set_new_evar(t_shell *shell, char *newvalue);
#endif
