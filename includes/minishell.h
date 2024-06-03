/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lefabreg <lefabreg@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 14:44:56 by pantoine          #+#    #+#             */
/*   Updated: 2024/06/03 13:26:57 by pantoine         ###   ########.fr       */
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
# include <errno.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <termios.h>
# include <unistd.h>
// libft
# include "../libft/libft.h"
// parsing
# include "lexing.h"

# define ONE "\001\033[0;31m\002p⃤"
# define TWO "\033[0;36me⃠꙱"
# define THREE "\033[0;93mt"
# define FOUR "\033[0;35mi⃞"
# define FIVE "\033[0;31mt⃟ "
# define SIX "\033[0;36m_꙱c꙱"
# define SEVEN "\033[0;93mo꙲"
# define EIGHT "\033[0;35mq⃢"
# define NINE "\033[0;31mu⃦"
# define TEN "\033[0;36mi⃫"
# define EL "\033[0;93ml⃞"
# define TW "\033[0;35ml"
# define THIR "\033[0;31ma⃐"
# define FOURT "\033[0;36mg⃫⃔"
# define FIFT "\033[0;93me⃡⃡⃡⃡⃕⃕"
# define END " \033[1;36m> \001\033[0m\002"

# ifndef T_CHILDPROCESS
#  define T_CHILDPROCESS

typedef struct s_childprocess
{
	int					error_pipe[2];
	pid_t				childprocess_pid;
}						t_childprocess;
# endif

// history
# ifndef T_DATA_H
#  define T_DATA_H

typedef struct s_data_h
{
	int					nb;
	char				*line;
}						t_data_h;
# endif

# ifndef T_HISTORY
#  define T_HISTORY

typedef struct s_history
{
	int					fd;
	int					size;
	t_list				*list;
	t_list				*node;
	t_data_h			*data;
}						t_history;
# endif

# ifndef T_SHELL
#  define T_SHELL

typedef struct s_shell
{
	int					argc;
	char				**argv;
	t_list				*envp;
	struct sigaction	catcher;
	char				**envp_char;
	int					previous_pipe;
	int					pipe_fds[2];
	t_childprocess		*children;
	t_history			history;
}						t_shell;
# endif

typedef enum s_sig_mode
{
	SIG_FG,
	SIG_HD,
	SIG_EXEC,
}						t_sig_mode;
/// functions prototype
// signals
# ifndef GLOBAL_SIG
#  define GLOBAL_SIG

extern unsigned char	g_current_sig;
# endif

void					free_history_data(void *data);

// copy and free envp
t_list					*copy_env(char **envp);
void					free_envp(t_list *envp);

void					ft_lst_display(t_list *lst);
void					free_history_data(void *data);
void					restore_history(t_history *history);
void					handle_history_error(t_list **list);
void					add_to_list(char *command, t_history *history);
void					add_to_history(char *command, t_history *history);

// get_next_line
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1000
# endif

char					*get_next_line(int fd);
char					*manage_line_with_n_for_buffer(char *buffer,
							size_t index);
char					*manage_line_with_n_for_line(char *buffer,
							size_t index);
char					*read_line(int fd, char *buffer, char *previous_line,
							int *bytes_read);
char					*helper(int fd, char *buffer, int bytes_read);
size_t					index_for_n(char *buffer);
int						check_eof(char *buffer, int bytes_read);

// parsing
void					split_word(char *command, t_shell *shell);
typedef struct s_cwds
{
	char				**sentence;
	int					i;
	int					j;
	int					count;
}						t_cwds;
typedef struct s_store_delim
{
	int					db_quote_open;
	int					s_quote_open;
	int					i;
	char				*delimiter;
	t_delims			**delims;
	int					cursor_tab;

}						t_store_delim;

#endif
