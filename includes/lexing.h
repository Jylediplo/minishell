/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyjy <jyjy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 14:07:51 by lefabreg          #+#    #+#             */
/*   Updated: 2024/05/31 00:41:22 by jyjy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXING_H
# define LEXING_H

# include "../libft/libft.h"
# include <stdlib.h>

typedef struct s_quote
{
	int			input_length;
	int			output_index;
	int			quote_open;
	int			i;
	char		current_quote;
	char		*output;
}				t_quote;

typedef struct s_delim
{
	char		**tokens;
	char		*del;
	char		*start;
	char		*end;
	int			index;

}				t_delim;

typedef struct s_delims
{
	int			index;
	char		*delim;
}				t_delims;

typedef struct s_lexer
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
	} e_flag;
	int			quote_removed;
	char		*content;
	int			dollar;
	int			index;
}				t_lexer;

typedef struct s_words
{
	int			len;
	int			in_s_q;
	int			in_db_q;
	int			in_dollar;
	int			word_start;
	char		**words;
	int			num_words;
	char		*command;
	char		**wds_delim;
	int			count_del;
	t_lexer		**lexer;

}				t_words;

typedef struct s_del
{
	int			i;
	int			count;
	char		*delimiter;
	char		*word;
	int			nb_delim;
	int			db_quote_open;
	int			s_quote_open;
	t_delims	**delims;

}				t_del;

typedef struct s_to_free
{
	t_list		*envp;
	char		*command;
	int			nb_delim;
	int			i;
	t_delims	**delims;
	int			nb_words;
	t_words		*words;

}				t_to_free;

int				is_builtin1(char *word, t_words *words, t_to_free *values);
int				is_builtin(char *word);
void			check_for_previous_builtins(t_words *words, int *previous_is_builtin,
		t_lexer **lexer, t_to_free *values);
// quotes
char			*manage_quotes(char *command, int *has_quotes);
int				check_quotes(char *command, t_list *envp);

// words spliting
void			split_words(t_words *words, t_list *envp, char *command);
void			create_words(t_words *words, int *i, t_list *envp,
					char *command);
void			check_words(t_words *words, t_list *envp, char *command);

// init/reset struct
void			reset_values(t_words *words);
void			init_words_struct(t_words *words, char *command);
void			init_struct_del(t_delim *delim, char *str);

// dollar handling
int				count_dollars(char *word);
void			dollars_handler(t_lexer **lexer, t_to_free *values,
					t_words *words, int *previous);

// lexer
void			handle_lexer(t_words *words, int *previous_is_builtin,
					t_to_free *values);
void			create_wds_lexer(t_words *words, t_to_free *values);

// delimiters
int				is_matching(char *word, char *token, size_t length,
					int *previous);
int				count_delim(char *word);
t_delims		**create_tab_delim(char *word, int nb_delim, t_to_free *values,
					t_words *words);
int				count_with_delim(t_delims **delims, int nb_delim, char *word);
char			**create_words_tab(t_delims **delims, int nb_delim, char *word,
					t_to_free *values);
char			delim(char *delimiter, char letter);
void			nb_words_with_delim(t_words *words, t_to_free *values);
void			manage_first_delim(t_del *del, char *word, t_delims **delims);

// free
void			free_wds_delim(t_words *words, int nb);
void			free_words(t_words *words);
void			free_temp_word(char **word);
void			free_lexer1(t_words *words, int index);
void			free_delim(t_delims **delim);
void			split_words_free(t_words *words, t_list *envp, char *command);
void			free_sentence(char **sentence);
void			free_delim_creation(t_delims **delims, char **sentence,
					t_to_free *values);

#endif
