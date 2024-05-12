/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lefabreg <lefabreg@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 14:44:56 by pantoine          #+#    #+#             */
/*   Updated: 2024/05/10 19:36:32 by lefabreg         ###   ########lyon.fr   */
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
typedef struct s_data_h
{
    int nb;
    char    *line;
}   t_data_h;

typedef struct s_history
{
    int fd;
    int size;
    t_list  *list;
    t_list  *node;
    t_data_h   *data;
}   t_history;

void	ft_lst_display(t_list *lst);
void    free_history_data(void	*data);
void    restore_history(t_history *history);
void	handle_history_error(t_list **list);
void    add_to_list(char *command, t_history *history);
void    add_to_history(char *command, t_history *history);
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
typedef	struct s_lexer
{
	enum
	{
		UNKNOWN = 258,
		WORD = 259,
		PIPE = 260,
		GREATER = 261,
        LESSER = 262,
        BUILTIN = 263,
        HEREDOC = 264,
        APPEND = 265,
        DELIMITER = 266,
    
	}	flag;
	char *content;
	int dollar;
} t_lexer;


void manage_path(char *cmd, char **envp);
char  *correct_path(char *argv, char **local_path);
char *find_path(char **envp);
int find_str(char *to_find, char *str);
void error(char *file, char **to_free1, char **to_free2);
void free_split(char **str);
void	split_word(char *command);
char *manage_quotes(char *command);
#endif
