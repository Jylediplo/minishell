/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pantoine <pantoine@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 23:37:51 by pantoine          #+#    #+#             */
/*   Updated: 2024/05/09 12:00:38 by pantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

# ifndef LEXER
#  define LEXER
typedef struct s_lexer
{
    int index;
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
    }    flag;
    char	*content;
    int		dollar;

} t_lexer;
# endif
typedef struct s_cmd
{
	/*
	 * tr a-z A-Z >> bonjour.txt >> bonjour2.txt << STOP
	 *
	 * "tr" WORD
	 * "a-z" WORD
	 * "A-Z" WORD 
	 * ">>" APPEND
	 * "bonjour.txt" WORD -> dup2(bonjour.txt, 1);
	 * ">>" APPEND
	 * "bonjour2.txt" WORD -> dup2(bonjour2.txt, bonjour.txt);
	 * "<<" HEREDOC
	 * "STOP" WORD
	 *
	 * {"tr", "a-z", "A-Z"}, out = bonjour.txt; dup2(bonjour2.txt, bonjour.txt), in = HEREDOC
	 */
	char	**command;
	int		size_cmd;
	char	*in;
	char	*out;
	int		index;
}	t_cmd;

# include "minishell.h"

//execute_main_size.c
int	get_cmdlist_size(char *input);
int	get_size_command(t_lexer **lexer, int *lexer_pos, t_list **cmds);

//execute_flags.c
int	add_size_arg_node(t_lexer **lexer, int *lexer_pos, t_list **cmds);
int	is_legal_token(t_lexer **lexer, int *lexer_pos, t_list *cmds);
int	is_legal_heredoc(t_lexer **lexer, int *lexer_pos, t_list *cmds);

//execute_heredocs.c
int	create_heredoc(char *delimiter, int *current_temp);
int	delete_heredocs(int nb_heredocs);

//execute_errors.c
void	malloc_exec_err(void);
void	unexpected_token_exec_err(char *error_token);
#endif
