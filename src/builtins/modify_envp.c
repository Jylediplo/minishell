/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modify_envp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pantoine <pantoine@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 15:23:37 by pantoine          #+#    #+#             */
/*   Updated: 2024/04/29 13:43:59 by pantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/evars.h"

char	*get_envvar_value(t_list *envp, char *envvar)
{
	t_list	*iter;
	size_t	len;
	char	*envp_value;
	char	*operator;

	iter = envp;
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
			&& *(envp_value + len) == '=')
			return (envp_value + len + 1);
		iter = iter->next;
	}
	return (NULL);
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
			iter->content = strjoin_free(iter->content,
				ft_strchr(newvar->content, '=') + 1);
			ft_lstdelone(newvar, free);
			return ;
		}
		iter = iter->next;
	}
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
		printf("Content of the new variable: <%s>\n", (char *)newvar->content);
		if (!get_envvar_value(shell->envp, (char *)newvar->content))
			ft_lstadd_back(&shell->envp, newvar);
		else
		{
			printf("Envvar already in the list -> modify operation\n");
			modify_envvar(shell->envp, newvar);
		}
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

void	free_envp(t_list *envp)
{
	t_list	*temp;

	while (envp)
	{
		temp = envp->next;
		free(envp->content);
		free(envp);
		envp = temp;
	}
}
