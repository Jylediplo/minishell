/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modify_envp_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pantoine <pantoine@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 18:58:33 by pantoine          #+#    #+#             */
/*   Updated: 2024/05/06 19:56:20 by pantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/evars.h"

char	*strjoin_free(char *s1, const char *s2)
{
	char	*res;

	res = ft_strjoin(s1, s2);
	if (!res)
	{
		free(s1);
		ft_putstr_fd("error: malloc failed\n", 2);
		return (NULL);
	}
	free(s1);
	return (res);
}

void	replace_content(t_list *current, t_list *to_del, char *newvalue)
{
	free(current->content);
	current->content = ft_strdup(newvalue);
	free(to_del->content);
	free(to_del);
	if (!current->content)
	{
		ft_putstr_fd("error: malloc failed\n", 2);
		ft_lstdelone(current, free);
	}
}

void	modify_envvar(t_list *envp, t_list *newvar)
{
	t_list	*iter;
	size_t	len;
	char	*envp_value;
	char	*newvar_value;

	iter = envp;
	newvar_value = newvar->content;
	len = ft_strchr(newvar_value, '=') - newvar_value;
	envp_value = NULL;
	while (iter)
	{
		envp_value = iter->content;
		if (!ft_strncmp(envp_value, newvar_value, len)
			&& envp_value[len] == '=')
		{
			replace_content(iter, newvar, newvar_value);
			return ;
		}
		iter = iter->next;
	}
}
