/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pantoine <pantoine@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 14:44:56 by pantoine          #+#    #+#             */
/*   Updated: 2024/05/27 16:37:41 by pantoine         ###   ########.fr       */
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
# include <sys/wait.h>
# include <errno.h>
// libft
# include "../libft/libft.h"
//parsing 
# include "lexing.h"
# ifndef T_SHELL
#  define T_SHELL

typedef struct s_shell
{
	int		argc;
	char	**argv;
	t_list	*envp;
	char	**envp_char;
	int		previous_pipe;
	int		pipe_fds[2];
	int		**error_pipes;
}	t_shell;
# endif

/// functions prototype
// signals
extern unsigned char	g_current_sig;
void	handle_signals(void);
void	free_history_data(void *data);

// copy and free envp
t_list	*copy_env(char **envp);
void	free_envp(t_list *envp);

// history
typedef struct s_data_h
{
	int		nb;
	char	*line;
}	t_data_h;

typedef struct s_history
{
	int			fd;
	int			size;
	t_list		*list;
	t_list		*node;
	t_data_h	*data;
}	t_history;

void	ft_lst_display(t_list *lst);
void	free_history_data(void	*data);
void	restore_history(t_history *history);
void	handle_history_error(t_list **list);
void	add_to_list(char *command, t_history *history);
void	add_to_history(char *command, t_history *history);
//
//get_next_line
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

char	*get_next_line(int fd);
char	*manage_line_with_n_for_buffer(char *buffer, size_t index);
char	*manage_line_with_n_for_line(char *buffer, size_t index);
char	*read_line(int fd, char *buffer, char *previous_line, int *bytes_read);
char	*helper(int fd, char *buffer, int bytes_read);
size_t	index_for_n(char *buffer);

//parsing
void	split_word(char *command, t_shell *shell);
typedef struct s_cwds
{
	char	**sentence;
	int		i;
	int		j;
	int		count;
}			t_cwds;
typedef struct s_store_delim
{
	int			db_quote_open;
	int			s_quote_open;
	int			i;
	char		*delimiter;
	t_delims	**delims;
	int			cursor_tab;

}				t_store_delim;

#endif
