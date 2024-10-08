/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   evars.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pantoine <pantoine@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 17:00:24 by pantoine          #+#    #+#             */
/*   Updated: 2024/05/31 11:14:54 by pantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EVARS_H
# define EVARS_H

# include "../libft/libft.h"
# include "execute.h"
# include <stdlib.h>
# include <stdio.h>

typedef struct s_evar
{
	enum
	{
		NONE,
		MALLOC,
		BAD_SUBSTITUTION,
		UNCLOSED_QUOTE,
		UNCLOSED_BRACE,
		INVALID_IDENTIFIER,
	}	e_error;
	struct
	{
		int		append;
		char	*plus_str;
		char	*equal_str;
		char	operator;
	}	s_change_evar;
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

void	get_evar(t_evar *evar, t_list *envp);
void	find_next_quotes(t_evar *evar, char *string, int index);
void	get_next_quotetype(t_evar *evar);
char	current_char(t_evar *evar);
void	copy_char(t_evar *evar);

//export_getsize.c
void	init_evar(t_evar *evar, char *newvalue, t_list *envp);

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

//export_identifier.c
int		valid_identifier_char(char c);
int		init_change_evar(t_shell *shell, t_evar *evar,
			char *parsed_command, int fd);

//handle_errors.c
void	evar_error_message(t_evar *evar, char *context, int fd);
void	malloc_error_dol(t_evar *evar);
void	set_err_status(t_evar *evar, int status);

//free_utils_export.c
void	free_envp(t_list *envp);
void	free_envp_exit(t_list *head);
void	free_envp_value_exit(t_list *head, char *value);

//export_main.c
int		export_envar(t_cmd *cmd, t_shell *shell);

//modify_envp.c
void	add_to_envp(t_shell *shell, t_evar *evar, char *value, int fd);
char	*get_envvar_value(t_list **envp, char *envvar);

//modify_envp_utils.c
char	*strjoin_free(char *s1, const char *s2, int fd);
void	modify_envvar(t_list *envp, t_list *newvar, int fd);

//echo_getsize.c
void	get_echo_size(t_evar *evar, t_list *envp);
char	*parse_echo(t_list *envp, char *to_echo, int fd);

//echo_setnew.c
void	get_echo(t_evar *evar, t_list *envp, int fd);

//echo_main.c
int		efftee_echo(char **cmd);

//unset_main.c
int		unset_envvar(t_cmd *cmd, t_shell *shell, int fd);

//env_main.c
int		show_me_the_way(t_list *envp);
//
//cd_main.c
int		change_directory(t_cmd *cmd, t_shell *shell);

//cd_utils.c
int		change_pwd(t_shell *shell, int fd, t_cmd *cmd);
int		change_oldpwd(t_shell *shell, char *old, t_cmd *cmd, int valid_current);
int		cd_error_message(char *message, int fd);

//exit_main.c
void	free_all_exit(t_lexer **lexer, t_list *cmdlist, t_shell *shell,
			int is_child);
int		exit_petitcoq(t_cmd *cmd, t_list *cmdlist,
			t_lexer **lexer, t_shell *shell);

//exit_utils.c
int		count_args_exit(t_cmd *cmd);
void	exit_single_arg(t_shell *shell, t_lexer **lexer,
			t_list *cmdlist, t_cmd *cmd);
void	exit_no_arg(t_shell *shell, t_lexer **lexer,
			t_list *cmdlist, t_cmd *cmd);

//pwd_main.c
void	get_pwd(int fd);

#endif
