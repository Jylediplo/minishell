/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pantoine <pantoine@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 11:19:17 by pantoine          #+#    #+#             */
/*   Updated: 2024/04/26 16:52:03 by pantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/evars.h"

char	**copy_env(char **envp)
{
	char	**res;
	char	len;
	int		i;

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
*	Input must be a string starting on the first character of the new variable.
*	For the new variable to be a valid identifier, it must only contain letters, numbers and underscores.
*/
int	export_envar(t_shell *shell, char *exportcommand)
{
	char	*parsed_command;
	t_evar	evar;

	(void)shell;
	parsed_command = parse_evar(exportcommand);
	if (!parsed_command)
		return (1);
	init_change_evar(&evar, parsed_command);
	free(parsed_command);
	return (0);
}
