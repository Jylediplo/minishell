/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   evars.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pantoine <pantoine@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 17:00:24 by pantoine          #+#    #+#             */
/*   Updated: 2024/04/18 19:37:48 by pantoine         ###   ########.fr       */
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
typedef struct  s_shell
{
    int     argc;
    char    **argv;
    char    **envp;
}   t_shell;
int		set_new_evar(t_shell *shell, char *newvalue);
void	get_evar(t_evar *evar);
void	find_next_quotes(t_evar *evar, char *string, int index);
int		allowed_in_braces(char c);
int		allowed_in_substitution(char c);
void	set_err_status(t_evar *evar, int status);
void	get_next_quotetype(t_evar *evar);
void	evar_error_message(t_evar *evar);

#endif
