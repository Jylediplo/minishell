/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pantoine <pantoine@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 18:48:29 by pantoine          #+#    #+#             */
/*   Updated: 2024/05/06 19:56:59 by pantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/evars.h"

void	remove_envvar(t_list **envp, char *to_remove)
{
	t_list	*iter;
	t_list	*previous;
	char	*envp_value;
	size_t	len;

	iter = *envp;
	if (!to_remove || !to_remove[0])
		return ;
	len = ft_strlen(to_remove);
	envp_value = NULL;
	while (iter)
	{
		envp_value = iter->content;
		if (!ft_strncmp(envp_value, to_remove, len)
			&& envp_value[len] == '=')
		{
			previous->next = iter->next;
			ft_lstdelone(iter, free);
			return ;
		}
		previous = iter;
		iter = iter->next;
	}
}

int	unset_envvar(t_shell *shell, char *unsetcommand)
{
	char	*parsed_command;
	t_evar	evar;

	parsed_command = parse_evar(&evar, unsetcommand, shell->envp);
	if (!parsed_command)
		return (1);
	remove_envvar(&shell->envp, parsed_command);
	free(parsed_command);
	while (evar.set_next)
	{
		parsed_command = parse_evar(&evar, evar.set_next, shell->envp);
		if (!parsed_command)
			return (1);
		remove_envvar(&shell->envp, parsed_command);
		free(parsed_command);
	}
	return (0);
}
