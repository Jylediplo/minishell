/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pantoine <pantoine@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 23:37:51 by pantoine          #+#    #+#             */
/*   Updated: 2024/05/07 00:05:24 by pantoine         ###   ########.fr       */
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
        NONE = 258,
        WORD = 259,
        PIPE = 260,
        GREATER = 261,
        LESSER = 262,
        BUILTIN = 263,
        HEREDOC = 264,
        APPEND = 265
    
    }    flag;
    char *content;
    int dollar;

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
	int		in;
	int		out;
}	t_cmd;

#endif
