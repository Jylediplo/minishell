/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   specials.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pantoine <pantoine@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 17:25:37 by pantoine          #+#    #+#             */
/*   Updated: 2024/04/10 12:20:54 by pantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char    **copy_env(char **envp)
{
    char    **res;
    char    len;
    int     i;

    i = 0;
    len = 0;
    while (envp[i])
    {
        len++;
        i++;
    }
    res = malloc(sizeof(char *) * (len + 1));
    if (!res)
        return (NULL);
    i = 0;
    while (envp[i])
    {
        res[i] = ft_strdup(envp[i]);
        i++;
    }
    res[i] = NULL;
    return (res);
}

/*
 * Input that needs to be received: VAR=varvalue. Unclosed quotes need not be interpreted.
 * We can receive double quotes, like VAR="'/bin/'", in which case the variable we remove the outer quotes
 * and the variable becomes VAR='/bin/'.
 * Example 1:
 *	VAR="'"'"/bin/"'"'" is valid syntax, the new variable will be "/bin/".
 *	The process is as follows:
 *	1)	"'" results in ', so final is (')'"/bin/"'"'"
 *	2)	String is then read as (')("/bin/")"'" since everything inside '' is a string literal.
 *	3)	We are left with "'" which is just ' on the right hand side.
 *	4) final output: (')("/bin/")(')
 * Example 2:
 *	VAR="'"/bin/"'" TEST is also valid syntax, we will simply discard TEST and proceed as in example 1.
 *	Expected output: '/bin/'.
 * Example 3:
 *	VAR="'"/bin/"'"TEST is valid and will result in '/bin/'TEST.
 * These three are valid, although if PATH is modified in such a way,
 * it will not be able to find any commands.
 * 
 * Parsing process:
 *	Step 1:
 *		Check for any blankspace between VAR and =. Error if any is detected.
 *	Step 2:
 *		Loop through the VALUE. If ' or " is found, find the next one and save anything that is inbetween
 *		if it does not contain $.
 *		If we have "'hello world...'''", we save 'hello world...''' and remove the outer quotes.
 *	Step 3:
 *		Look for $ if the current quote sequence started with ". Try to expand $ with its associated variable.
 *		If none is found, skip the $ and proceed with the rest of the quote.
 *		Example:
 *			"$TERM 'bonjour'" should result in the expansion of $TERM, in my case screen-256color followed by
 *			'bonjour'. The final result would be VAR=screen-256color 'bonjour'.
 *	NOTE:
 *		For now, command expansions are not supported. $(COMMAND) is not working.
 */
int    export_envar(t_shell *shell, char *newvalue)
{
    int     i;

	(void)shell;
    i = 0;
	(void)i;
	if (!ft_strchr(newvalue, '='))
		return (1);
	return (0);
    // temp = ft_split(to_change, '=');
    // if (!temp)
    //     return (1);
    // while (shell->envp[i])
    // {
    //     if (!ft_strncmp(temp[0], ft_strchr(shell->envp[i], '=') - shell->envp[i], ft_strlen(temp[0])) &&
    //         ft_strlen(temp[0]) == ft_strlen(ft_strchr(shell->envp[i], '=') - shell->envp[i]))
    //     shell->envp[i] = ft_strchr(to_change, '=') + 1;
    // }
}
/*
void    unset_envar(t_shell *shell)
{

}*/
