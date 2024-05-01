/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   evars.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pantoine <pantoine@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 17:00:24 by pantoine          #+#    #+#             */
/*   Updated: 2024/05/01 19:20:51 by pantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EVARS_H
# define EVARS_H

# include "../libft/libft.h"
# include <stdlib.h>
# include <stdio.h>

extern int	g_current_sig;
typedef struct s_evar
{
	enum
	{
		NONE,
		MALLOC,
		BAD_SUBSTITUTION,
		UNCLOSED_QUOTE,
		UNCLOSED_BRACE,
		STOP,
		INVALID_IDENTIFIER,
	}	error;
	struct
	{
		int		append;
		char	*plus_str;
		char	*equal_str;
		char	operator;
	}	change_evar;
	int		size_evar;
	int		size_expanded_var;
	int		id_toset;
	int		id_copy;
	int		questionmarks;
	char	quotetype;
	char	*newvalue;
	char	*newvalue_copy;
	char	*newvalue_toset;
	char	*single_qchar;
	char	*double_qchar;
	char	*dol_expansion_variable;
	char	*dol_expansion_value;
	char	*set_next;
}	t_evar;
# ifndef T_SHELL
#  define T_SHELL
typedef struct  s_shell
{
    int     argc;
    char    **argv;
	t_list	*envp;
}   t_shell;
# endif
char	*parse_evar(t_evar *evar, char *newvalue, t_list *envp);
void	get_evar(t_evar *evar, t_list *envp);
void	find_next_quotes(t_evar *evar, char *string, int index);
void	get_next_quotetype(t_evar *evar);
char	current_char(t_evar *evar);
void	copy_char(t_evar *evar);

//export_getsize.c
void	init_evar(t_evar *evar, char *newvalue);

//export_utils.c
void	increase_expanded_var_size(t_evar *evar);
void	increase_expanded_var_size_and_index(t_evar *evar);
void	increase_size_evar(t_evar *evar);

//export_substitutions.c
void	size_dol_substitution(t_evar *evar, int inside, t_list *envp);
void	get_expanded_size(t_evar *evar, t_list *envp);
void	expand_dol(t_evar *evar, int inside, t_list *envp);
void	substitute_var(t_evar *evar, t_list *envp);

//export_substitutions_utils.c
int		is_whitespace(char c);
int		count_single_dollar(t_evar *evar, int inside);
int		copy_single_dollar(t_evar *evar, int inside);

//export_sub_lastsig.c
int		get_exitsig_size(t_evar *evar);
int		copy_exitsig_value(t_evar *evar);
void	trigger_exitsig_copy_handler(t_evar *evar, t_list *envp);
void	trigger_exitsig_size_handler(t_evar *evar, t_list *envp);

//export_sub_lastsig_utils.c
int		handle_questionmarks_in_braces_size(t_evar *evar);
int		handle_questionmarks_in_braces_copy(t_evar *evar);
int		is_legal_sigsub_count(t_evar *evar);
int		is_legal_sigsub_copy(t_evar *evar);

//export_identifier.c
int		valid_identifier(char *identifier, char operator);
int		valid_identifier_char(char c);
void	init_change_evar(t_shell *shell, t_evar *evar, char *parsed_command);

//export_identifier_utils.c
char	*save_next_evar(t_evar *evar);

//handle_errors.c
void	evar_error_message(t_evar *evar);
void	malloc_error_dol(t_evar *evar);
void	set_err_status(t_evar *evar, int status);

//export_main.c
int		export_envar(t_shell *shell, char *exportcommand);

//modify_envp.c
void	print_envp(t_list *envp);
void	free_envp(t_list *envp);
void	add_to_envp(t_shell *shell, t_evar *evar, char *value);
char	*get_envvar_value(t_list **envp, char *envvar);

//modify_envp_utils.c
char	*strjoin_free(char *s1, const char *s2);
void	modify_envvar(t_list *envp, t_list *newvar);

//echo_getsize.c
char	*parse_echo(t_list *envp, char *to_echo);

//echo_setnew.c
void	get_echo(t_evar *evar, t_list *envp);

//echo_main.c
int	efftee_echo(t_shell *shell, char *to_echo);

//unset_main.c
void	remove_envvar(t_list **envp, char *to_remove);
int		unset_envvar(t_shell *shell, char *unsetcommand);
#endif
