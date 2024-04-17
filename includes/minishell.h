/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pantoine <pantoine@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 14:44:56 by pantoine          #+#    #+#             */
/*   Updated: 2024/04/17 15:53:52 by pantoine         ###   ########.fr       */
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
	enum
	{
		NONE,
		MALLOC,
		BAD_SUBSTITUTION,
		UNCLOSED_QUOTE,
	}	error;
	int		size_evar;
	int		size_expanded_var;
	int		id_toset;
	int		id_copy;
	char	*newvalue;
	char	*newvalue_copy;
	char	*newvalue_toset;
	char	*single_qchar;
	char	*double_qchar;
	char	*dol_expansion_variable;
	char	*dol_expansion_value;
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
void	get_evar(t_evar *evar);
int		allowed_in_braces(char c);
void	evar_error_message(t_evar *evar);
#endif
