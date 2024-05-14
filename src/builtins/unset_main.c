/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pantoine <pantoine@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 18:48:29 by pantoine          #+#    #+#             */
/*   Updated: 2024/05/14 18:02:14 by pantoine         ###   ########.fr       */
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

int	unset_envvar(t_cmd *cmd, t_shell *shell)
{
	int	i;

	i = 1;
	while (cmd->command[i])
		remove_envvar(&shell->envp, cmd->command[i++]);
	return (0);
}
