/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modify_envp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pantoine <pantoine@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 15:23:37 by pantoine          #+#    #+#             */
/*   Updated: 2024/05/27 19:03:57 by pantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/evars.h"

char	*get_envvar_value(t_list **envp, char *envvar)
{
	t_list	*iter;
	size_t	len;
	char	*envp_value;
	char	*operator;

	iter = *envp;
	if (!envvar || !envvar[0])
		return (NULL);
	operator = ft_strchr(envvar, '=');
	if (operator)
		len = operator - envvar;
	else
		len = ft_strlen(envvar);
	envp_value = NULL;
	while (iter)
	{
		envp_value = iter->content;
		if (!ft_strncmp(envp_value, envvar, len)
			&& envp_value[len] == '=')
			return (envp_value + len + 1);
		iter = iter->next;
	}
	return (NULL);
}

static int	remove_plus_in_envvar(t_list *newvar, int fd)
{
	char	*value;
	char	*res;
	char	*plus_operator;
	int		len;

	value = newvar->content;
	plus_operator = ft_strchr(value, '+');
	len = plus_operator - value;
	res = malloc(sizeof(char) * (ft_strlen(value)));
	if (!res)
	{
		perror_context("malloc", NULL, fd);
		free(newvar->content);
		free(newvar);
		return (1);
	}
	ft_memcpy(res, value, len);
	ft_memcpy(res + len, plus_operator + 1, ft_strlen(value) - len);
	free(newvar->content);
	newvar->content = res;
	return (0);
}

static void	append_to_envvar(t_list *envp, t_list *newvar, int fd)
{
	t_list	*iter;
	size_t	len;
	char	*envp_value;
	char	*newvar_value;

	iter = envp;
	newvar_value = newvar->content;
	len = ft_strchr(newvar_value, '+') - newvar_value;
	envp_value = NULL;
	while (iter)
	{
		envp_value = iter->content;
		if (!ft_strncmp(envp_value, newvar_value, len)
			&& envp_value[len] == '=')
		{
			iter->content = strjoin_free(iter->content,
					ft_strchr(newvar->content, '=') + 1, fd);
			ft_lstdelone(newvar, free);
			return ;
		}
		iter = iter->next;
	}
	if (remove_plus_in_envvar(newvar, fd))
		return ;
	ft_lstadd_back(&envp, newvar);
}

void	add_to_envp(t_shell *shell, t_evar *evar, char *value, int fd)
{
	char	*value_dup;
	t_list	*newvar;

	value_dup = ft_strdup(value);
	if (!value_dup)
	{
		perror_context("malloc", NULL, fd);
		return ;
	}
	newvar = ft_lstnew(value_dup);
	if (!newvar)
	{
		free(value_dup);
		perror_context("malloc", NULL, fd);
		return ;
	}
	if (!evar->s_change_evar.append)
	{
		if (!get_envvar_value(&shell->envp, (char *)newvar->content))
			ft_lstadd_back(&shell->envp, newvar);
		else
			modify_envvar(shell->envp, newvar, fd);
		return ;
	}
	append_to_envvar(shell->envp, newvar, fd);
}
