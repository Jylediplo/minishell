/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pantoine <pantoine@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 11:19:17 by pantoine          #+#    #+#             */
/*   Updated: 2024/05/01 16:08:51 by pantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/evars.h"

t_list	*copy_env(char **envp)
{
	int		i;
	t_list	*envvar;
	t_list	*head;
	char	*value;

	i = 1;
	value = ft_strdup(envp[0]);
	if (!value)
		exit(EXIT_FAILURE);
	head = ft_lstnew(value);
	if (!head)
	{
		free(value);
		exit(EXIT_FAILURE);
	}
	while (envp[i])
	{
		value = ft_strdup(envp[i]);
		if (!value)
		{
			free_envp(head);
			exit(EXIT_FAILURE);
		}
		envvar = ft_lstnew(value);
		if (!envvar)
		{
			free(value);
			free_envp(head);
			exit(EXIT_FAILURE);
		}
		ft_lstadd_back(&head, envvar);
		i++;
	}
	return (head);
}

/*
*	Input must be a string starting on the first character of the new variable.
*	For the new variable to be a valid identifier, it must only contain letters, numbers and underscores.
*/
int	export_envar(t_shell *shell, char *exportcommand)
{
	char	*parsed_command;
	t_evar	evar;

	parsed_command = parse_evar(&evar, exportcommand, shell->envp);
	if (!parsed_command)
		return (1);
	init_change_evar(shell, &evar, parsed_command);
	while (evar.set_next)
	{
		parsed_command = parse_evar(&evar, evar.set_next, shell->envp);
		if (!parsed_command)
			return (1);
		init_change_evar(shell, &evar, parsed_command);
	}
	return (0);
}
