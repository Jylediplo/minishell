/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modify_envp_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pantoine <pantoine@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 18:58:33 by pantoine          #+#    #+#             */
/*   Updated: 2024/04/30 15:49:14 by pantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/evars.h"

char	*strjoin_free(char *s1, const char *s2)
{
	char	*res;

	(void)s2;
	res = ft_strjoin(s1, s2);
	if (!res)
	{
		free(s1);
		ft_putstr_fd("error: malloc failed\n", 2);
		return (NULL);
	}
	return (res);
}

void	modify_envvar(t_list *envp, t_list *newvar)
{
	t_list	*iter;
	size_t	len;
	char	*envp_value;
	char	*newvar_value;

	iter = envp;
	newvar_value = (char *)newvar->content;
	len = ft_strchr(newvar_value, '=') - newvar_value;
	envp_value = NULL;
	while (iter)
	{
		envp_value = iter->content;
		if (!ft_strncmp(envp_value, newvar_value, len)
			&& envp_value[len] == '=')
		{
			free(iter->content);
			iter->content = ft_strdup(newvar_value);
			ft_lstdelone(newvar, free);
			if (!iter->content)
			{
				ft_putstr_fd("error: malloc failed\n", 2);
				ft_lstdelone(iter, free);
			}
			return ;
		}
		iter = iter->next;
	}
}
