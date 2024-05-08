/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils_export.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pantoine <pantoine@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 19:11:50 by pantoine          #+#    #+#             */
/*   Updated: 2024/05/07 16:46:26 by pantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/evars.h"

void	free_list(t_list *lst)
{
	t_list	*temp;

	while (lst)
	{
		temp = lst->next;
		free(lst);
		lst = temp;
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

void	free_value_exit(char *value)
{
	free(value);
	exit(EXIT_FAILURE);
}

void	free_envp_value_exit(t_list *head, char *value)
{
	free(value);
	free_envp(head);
	exit(EXIT_FAILURE);
}

void	free_envp_exit(t_list *head)
{
	free_envp(head);
	exit(EXIT_FAILURE);
}
