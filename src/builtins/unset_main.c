/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pantoine <pantoine@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 18:48:29 by pantoine          #+#    #+#             */
/*   Updated: 2024/05/24 14:09:47 by pantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/evars.h"

static int	is_valid_unset(char *to_remove)
{
	int		i;
	t_evar	evar;

	i = 0;
	if (to_remove[i] >= '0' && to_remove[i] <= '9')
	{
		evar.e_error = INVALID_IDENTIFIER;
		evar_error_message(&evar, to_remove);
		return (0);
	}
	i++;
	while (to_remove[i])
	{
		if (!valid_identifier_char(to_remove[i++]))
		{
			evar.e_error = INVALID_IDENTIFIER;
			evar_error_message(&evar, to_remove);
			return (0);
		}
	}
	return (1);
}

static int	remove_envvar(t_list **envp, char *to_remove)
{
	t_list	*iter;
	t_list	*previous;
	char	*envp_value;
	size_t	len;

	iter = *envp;
	if (!to_remove || !to_remove[0])
		return (0);
	len = ft_strlen(to_remove);
	while (iter)
	{
		envp_value = iter->content;
		if (!ft_strncmp(envp_value, to_remove, len)
			&& envp_value[len] == '=')
		{
			previous->next = iter->next;
			ft_lstdelone(iter, free);
			return (0);
		}
		previous = iter;
		iter = iter->next;
	}
	if (!is_valid_unset(to_remove))
		return (1);
	return (0);
}

int	unset_envvar(t_cmd *cmd, t_shell *shell)
{
	int	i;
	int	last_sigerror;

	i = 1;
	last_sigerror = 0;
	while (cmd->command[i])
	{
		if (remove_envvar(&shell->envp, cmd->command[i++]))
			last_sigerror = g_current_sig;
	}
	if (last_sigerror)
		g_current_sig = last_sigerror;
	return (0);
}
