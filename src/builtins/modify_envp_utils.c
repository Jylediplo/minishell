/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modify_envp_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pantoine <pantoine@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 18:58:33 by pantoine          #+#    #+#             */
/*   Updated: 2024/05/26 18:25:34 by pantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/evars.h"

char	*strjoin_free(char *s1, const char *s2)
{
	char	*res;

	res = ft_strjoin(s1, s2);
	if (!res)
	{
		perror_context("malloc", NULL);
		return (s1);
	}
	free(s1);
	return (res);
}

static void	replace_content(t_list *current, t_list *to_del, char *newvalue)
{
	char	*temp;

	temp = ft_strdup(newvalue);
	if (!temp)
	{
		perror_context("malloc", NULL);
		ft_lstdelone(to_del, free);
		return ;
	}
	free(current->content);
	current->content = temp;
	free(to_del->content);
	free(to_del);
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
