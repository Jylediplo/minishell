/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pantoine <pantoine@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 11:42:01 by pantoine          #+#    #+#             */
/*   Updated: 2024/04/10 23:40:34 by pantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// void	dollar_expansion(t_shell *shell, char *newvalue)
// {
// }
//
/*
 *	Start on a quote (either ' or ") and go through the string until a matching quote is found.
 *	Count all characters and handle dollar expansion with getent(VAR).
 *	Return a pointer to the newvalue starting right after the matched quote. The string must be checked if it ended
 *	after the call to the function.
 *	Example:
 *		newvar = "hello 'world!'"'test'
 *		-> size_evar will increase by 13 (since we include the last quote)
 *		-> Returned pointer will be 'test'.
 *	newvar can then be sent again in the loop to parse 'test'.
 */
char	*handle_quoted_sequence(t_shell *shell, char *newvalue, int *size_evar, char type)
{
	(void)shell;
	while (*newvalue != type)	
	{
		if (*newvalue == '$' && type == '\"')
			continue ;//dollar_expansion();
		*size_evar += 1;
		newvalue += 1;
	}
	newvalue += 1;
	return (newvalue);
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
int	parse_evar(t_shell *shell, char *newvalue)
{
	int		size_evar;

	size_evar = 0;
	while (*newvalue)
	{
		if (!ft_strchr(newvalue, '\"') && ft_strchr(newvalue, '\''))
		{
			if (!ft_strchr(newvalue + 1, '\''))
				return (1); //unclosed quote sequence
			// SKIP AND COUNT UNTIL CHAR IS MET
			newvalue = handle_quoted_sequence(shell, ft_strchr(newvalue, '\'') + 1, &size_evar, '\'');
			if (!newvalue)
				break ;
		}
		else if (ft_strchr(newvalue, '\"') && !ft_strchr(newvalue, '\''))
		{
			if (!ft_strchr(newvalue + 1, '\"'))
				return (1); //unclosed quote sequence
			// SKIP AND COUNT UNTIL CHAR IS MET
			newvalue = handle_quoted_sequence(shell, ft_strchr(newvalue, '\"') + 1, &size_evar, '\"');
			if (!newvalue)
				break ;
		}
		else if (ft_strchr(newvalue, '\"') < ft_strchr(newvalue, '\''))
		{
			if (!ft_strchr(newvalue + 1, '\"'))
				return (1); //unclosed quote sequence
			// SKIP AND COUNT UNTIL CHAR IS MET
			newvalue = handle_quoted_sequence(shell, ft_strchr(newvalue, '\"') + 1, &size_evar, '\"');
			if (!newvalue)
				break ;
		}
		else if (ft_strchr(newvalue, '\"') > ft_strchr(newvalue, '\''))
		{
			if (!ft_strchr(newvalue + 1, '\''))
				return (1); //unclosed quote sequence
			// SKIP AND COUNT UNTIL CHAR IS MET
			newvalue = handle_quoted_sequence(shell, ft_strchr(newvalue + 1, '\''), &size_evar, '\'');
			if (!newvalue)
				break ;
		}
		else
		{
			newvalue++;
			size_evar++;
		}
	}
	return (size_evar);
}
