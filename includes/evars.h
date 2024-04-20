/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   evars.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pantoine <pantoine@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 17:00:24 by pantoine          #+#    #+#             */
/*   Updated: 2024/04/21 00:26:52 by pantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EVARS_H
# define EVARS_H

# include "../libft/libft.h"
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
		STOP,
	}	error;
	int		size_evar;
	int		size_expanded_var;
	int		id_toset;
	int		id_copy;
	char	quotetype;
	char	*newvalue;
	char	*newvalue_copy;
	char	*newvalue_toset;
	char	*single_qchar;
	char	*double_qchar;
	char	*dol_expansion_variable;
	char	*dol_expansion_value;
}	t_evar;
# ifndef T_SHELL
#  define T_SHELL
typedef struct  s_shell
{
    int     argc;
    char    **argv;
    char    **envp;
}   t_shell;
# endif
char	*set_new_evar(t_shell *shell, char *newvalue);
void	get_evar(t_evar *evar);
void	find_next_quotes(t_evar *evar, char *string, int index);
int		allowed_in_braces(char c);
int		allowed_in_substitution(char c);
void	get_next_quotetype(t_evar *evar);
void	evar_error_message(t_evar *evar);
void	increase_expanded_var_size(t_evar *evar);
void	increase_size_evar(t_evar *evar);
char	current_char(t_evar *evar);
void	copy_char(t_evar *evar);

//export_substitutions.c
void	size_dol_substitution(t_evar *evar, int inside);
void	get_expanded_size(t_evar *evar);
void	expand_dol(t_evar *evar, int inside);
void	substitute_var(t_evar *evar);

//handle_errors.c
void	malloc_error_dol(t_evar *evar);
void	set_err_status(t_evar *evar, int status);
#endif
