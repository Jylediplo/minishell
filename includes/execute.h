/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pantoine <pantoine@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 23:37:51 by pantoine          #+#    #+#             */
/*   Updated: 2024/05/11 21:04:46 by pantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

# define HDNAME ".hdtmp"
# include "minishell.h"
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
	char	*tempfile_name;
	t_list	*cmd_args;
	int		size_cmd;
	int		in;
	int		out;
}	t_cmd;

//execute_main_size.c
int		add_arg_to_cmd(int *lexer_pos, t_cmd *cmd, char *newarg_content);
int		filter_type_input(t_lexer **lexer, int *lexer_pos, t_list **cmds);
t_list	*create_begin_cmd(t_cmd *begin_cmd, char *begin);
t_list	*init_cmdlist_size(void);
int		get_cmdlist(char *input, t_list *envp);

//execute_flags.c
int		get_size_command(t_lexer **lexer, int *lexer_pos, t_cmd *cmd);
int		set_cmdargs_basevalues(t_lexer **lexer, int *lexer_pos, t_cmd *cmd);
t_cmd	*init_cmdargs(t_lexer **lexer, int *lexer_pos);
int		add_size_arg_node(t_lexer **lexer, int *lexer_pos, t_list **cmds);

//execute_heredocs.c
char	*name_tempfile(t_cmd *cmd);
int		open_temp(char *filename);
int		create_heredoc(char *delimiter, t_cmd *cmd);

//execute_errors.c
int		newcmd_malloc_err(t_cmd *cmd);
void	unexpected_token_exec_err(char *error_token);
void	perror_context(char *failed_command, char *context);

//execute_free_utils.c
void	close_fds_remove_tmps(t_cmd *cmd);
void	free_single_cmd(t_list *args);
void	free_cmdlist(t_list *cmds);
void	free_lexer(t_lexer **lexer);

//execute_set_redirections.c
int		redirect_stream(t_lexer **lexer, int *lexer_pos, t_cmd *cmd);
int		is_legal_token(t_lexer **lexer, int *lexer_pos, t_cmd *cmd);
int		is_legal_heredoc(t_lexer **lexer, int *lexer_pos, t_cmd *cmd);

//execute_utils.c
int		flag_redirect_stream(t_lexer **lexer, int *lexer_pos);
int		flag_add_to_node(t_lexer **lexer, int *lexer_pos);
#endif
