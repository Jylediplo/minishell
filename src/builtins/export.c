/* ************************************************************************** */
/*                                                                           */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pantoine <pantoine@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 11:42:01 by pantoine          #+#    #+#             */
/*   Updated: 2024/04/17 14:57:57 by pantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/evars.h"

int	allowed_in_braces(char c)
{
	if (c != '\'' && c != '\"' && c != ' ' && c != '{')
		return (1);
	return (0);
}

void	set_err_status(t_evar *evar, int status)
{
	evar->error = status;
}

void	increase_expanded_var_size(t_evar *evar)
{
	evar->size_expanded_var++;
	evar->newvalue++;
}

void	increase_size_evar(t_evar *evar)
{
	evar->newvalue++;
	evar->size_evar++;
}

void	init_evar(t_evar *evar, char *newvalue)
{
	evar->size_evar = 0;
	evar->id_toset = 0;
	evar->id_copy = 0;
	find_next_quotes(evar, newvalue, 0);
	evar->newvalue = newvalue;
	evar->newvalue_toset = NULL;
	evar->error = NONE;
}

/*
 *	Start on a quote (either ' or ") and go through the string until a matching quote is found.
 *	Count all characters and handle dollar expansion with getent(VAR).
 *	Return a pointer to the newvalue starting right after the matched quote. The string must be checked if it ended
 *	after the call to the function.
 *	Example:
 *		newvar = "hello 'world!'"'test'
 *		-> size_evar will increase by 14, or up until the second ".
 *		-> Returned pointer will be 'test'; it must always be AFTER the matched quote.
 *	newvar can then be sent again in the loop to parse 'test'.
 */
char	*parse_quoted_sequence(t_evar *evar, char quotetype)
{
	if (!ft_strchr(evar->newvalue + 1, quotetype))
		return (set_err_status(evar, UNCLOSED_QUOTE), NULL);
	while (*evar->newvalue != quotetype && evar->error != BAD_SUBSTITUTION)
	{
		if (*evar->newvalue == '$')
			size_dol_substitution(evar);
		else if (*evar->newvalue == ' ')
			return (set_err_status(evar, STOP), NULL);
		else
			increase_size_evar(evar);
	}
	evar->newvalue++;
	while (*evar->newvalue != quotetype && evar->error != BAD_SUBSTITUTION && evar->error != MALLOC)
	{
		if (*evar->newvalue == '$' && quotetype == '\"')
			size_dol_substitution(evar);
		else
			increase_size_evar(evar);
	}
	if (*evar->newvalue)
		evar->newvalue += 1;
	return (evar->newvalue);
}

void	get_next_quotetype(t_evar *evar)
{
	if ((!evar->double_qchar && evar->single_qchar)
		|| (evar->double_qchar > evar->single_qchar && evar->single_qchar))
	{
		evar->quotetype = '\'';
		return ;
	}
	else if ((evar->double_qchar && !evar->single_qchar)
		|| (evar->double_qchar < evar->single_qchar && evar->double_qchar))
	{
		evar->quotetype = '\"';
		return ;
	}
	evar->quotetype = '\0';
	return ;
}

void	get_evar_size(t_evar *evar)
{
	while (*evar->newvalue)
	{
		get_next_quotetype(evar);
		if (evar->quotetype)
			evar->newvalue = parse_quoted_sequence(evar, evar->quotetype);
		else if (!evar->quotetype)
		{
			if (*evar->newvalue == '$')
				size_dol_substitution(evar);
			else if (*evar->newvalue == ' ')
				return (set_err_status(evar, STOP));
			else
				increase_size_evar(evar);
		}
		if (evar->error == BAD_SUBSTITUTION || evar->error == MALLOC || !evar->newvalue) //last cond if UNCLOSED_QUOTE or STOP
			return ;
		find_next_quotes(evar, evar->newvalue, 0);
	}
}

/*
 * This function parses the value part of the export command. The usual format of export is VAR=VALUE.
 * It is assumed here that the format is correct, and we are only treating VALUE itself, named newvalue in
 * what follows.
 * Step 1:
 *		Get the size of the evar value. We first expand quotes, and then any dollar expansion is performed inside
 *		" quotes.
 * Step 2:
 *		Use the newly created buffer to fill it with a quote and dollar expanded version of newvalue.
 * Step 3:
 *		Return the parsed newvalue.
*/
int	set_new_evar(t_shell *shell, char *newvalue)
{
	t_evar	evar;

	(void)shell;
	init_evar(&evar, newvalue);
	get_evar_size(&evar);
	if (evar.error != NONE && evar.error != STOP)
	{
		evar_error_message(&evar);
		return (1);
	}
	evar.error = NONE;
	evar.newvalue_copy = ft_strdup(newvalue);
	evar.newvalue_toset = (char *)malloc(sizeof(char) * (evar.size_evar + 1));
	if (!evar.newvalue_toset)
		return (1);
	get_evar(&evar);
	if (evar.error != MALLOC)
		printf("New evar value: >%s<\n", evar.newvalue_toset);
	free(evar.newvalue_copy);
	free(evar.newvalue_toset);
	return (0);
}
