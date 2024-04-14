/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pantoine <pantoine@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 14:44:56 by pantoine          #+#    #+#             */
/*   Updated: 2024/04/10 12:17:08 by pantoine         ###   ########.fr       */
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

typedef struct s_evar
{
	int		size_evar;
	char	current_parsed_quote;
	char	*newvalue;
	char	*single_qchar;
	char	*double_qchar;
	char	*dol_expansion;
}	t_evar;
typedef struct  s_shell
{
    int     argc;
    char    **argv;
    char    **envp;
}   t_shell;

/// functions prototype
// signals
extern int	g_current_sig;
void		handle_signals(void);

void		free_history_data(void *data);

// env variables and export functions
char    **copy_env(char **envp);
int    	export_envar(t_shell *shell, char *to_change);
int		set_new_evar(t_shell *shell, char *newvalue);
#endif
