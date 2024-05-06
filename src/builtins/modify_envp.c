/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modify_envp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pantoine <pantoine@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 15:23:37 by pantoine          #+#    #+#             */
/*   Updated: 2024/05/06 19:41:19 by pantoine         ###   ########.fr       */
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

void	remove_plus_in_envvar(t_list *newvar)
{
	char	*value;
	char	*res;
	char	*plus_operator;
	int		len;

	value = newvar->content;
	plus_operator = ft_strchr(value, '+');
	len = plus_operator - value;
	res = (char *)malloc(sizeof(char) * (ft_strlen(value)));
	ft_memcpy(res, value, len);
	ft_memcpy(res + len, plus_operator + 1, ft_strlen(value) - len);
	free(newvar->content);
	newvar->content = res;
}

void	append_to_envvar(t_list *envp, t_list *newvar)
{
	t_list	*iter;
	size_t	len;
	char	*envp_value;
	char	*newvar_value;

	iter = envp;
	newvar_value = (char *)newvar->content;
	len = ft_strchr(newvar_value, '+') - newvar_value;
	envp_value = NULL;
	while (iter)
	{
		envp_value = iter->content;
		if (!ft_strncmp(envp_value, newvar_value, len)
			&& envp_value[len] == '=')
		{
			printf("Append to the following: <%s>\n", envp_value);
			iter->content = strjoin_free(iter->content,
					ft_strchr(newvar->content, '=') + 1);
			ft_lstdelone(newvar, free);
			return ;
		}
		iter = iter->next;
	}
	remove_plus_in_envvar(newvar);
	ft_lstadd_back(&envp, newvar);
}

void	add_to_envp(t_shell *shell, t_evar *evar, char *value)
{
	t_list	*newvar;

	newvar = ft_lstnew(value);
	if (!newvar)
	{
		ft_putstr_fd("error: malloc failed\n", 2);
		return ;
	}
	if (!evar->change_evar.append)
	{
		if (!get_envvar_value(&shell->envp, (char *)newvar->content))
			ft_lstadd_back(&shell->envp, newvar);
		else
			modify_envvar(shell->envp, newvar);
		return ;
	}
	append_to_envvar(shell->envp, newvar);
}

void	print_envp(t_list *envp)
{
	t_list	*iter;

	iter = envp;
	while (iter)
	{
		printf("%s\n", (char *)iter->content);
		iter = iter->next;
	}
}
