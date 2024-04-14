/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pantoine <pantoine@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 11:42:01 by pantoine          #+#    #+#             */
/*   Updated: 2024/04/11 10:33:36 by pantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// void	dollar_expansion(t_shell *shell, char *newvalue)
// {
// }
//
void	init_evar(t_evar *evar, char *newvalue)
{
	evar->size_evar = 0;
	evar->single_qchar = ft_strchr(newvalue, '\'');
	evar->double_qchar = ft_strchr(newvalue, '\"');
	evar->newvalue = newvalue;
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
		return (NULL);
	while (*evar->newvalue != quotetype)
	{
		evar->newvalue++;
		evar->size_evar++;
	}
	evar->newvalue++;
	while (*evar->newvalue != quotetype)	
	{
		if (*evar->newvalue == '$' && quotetype == '\"')
			continue ;//dollar_expansion();
		evar->size_evar++;
		evar->newvalue += 1;
	}
	if (*evar->newvalue)
		evar->newvalue += 1;
	return (evar->newvalue);
}

/*
 * First step of exporting a new env variable, we get the size of the env var through this function.
 * It skips quotes which must be skipped and counts space required for dollar expansions (if any).
 * This function does not have a return value since we are directly changing the value value inside the struct
 * pointer. However, result must sill be checked after it is called since a -1 value indicates an unclosed quote.
 */
void	get_evar_size(t_evar *evar)
{
	while (*evar->newvalue)
	{
		if ((!evar->double_qchar && evar->single_qchar) || (evar->double_qchar > evar->single_qchar && evar->single_qchar))
			evar->newvalue = parse_quoted_sequence(evar, '\'');
		else if ((evar->double_qchar && !evar->single_qchar) || (evar->double_qchar < evar->single_qchar && evar->double_qchar))
			evar->newvalue = parse_quoted_sequence(evar, '\"');
		else if (!evar->double_qchar && !evar->single_qchar)
		{
			evar->newvalue++;
			evar->size_evar++;
		}
		if (!evar->newvalue)
		{
			evar->size_evar = -1;
			break ;
		}
		if (!*evar->newvalue)
			break ;
		evar->double_qchar = ft_strchr(evar->newvalue, '\"');
		evar->single_qchar = ft_strchr(evar->newvalue, '\'');
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
	printf("Evar size: %d\n", evar.size_evar);
	return (0);
}
