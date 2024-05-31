/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils_export.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pantoine <pantoine@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 19:11:50 by pantoine          #+#    #+#             */
/*   Updated: 2024/05/31 21:31:50 by pantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/evars.h"

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

void	free_envp_value_exit(t_list *head, char *value)
{
	perror_context("malloc", NULL, 2);
	free(value);
	free_envp(head);
	exit(g_current_sig);
}

void	free_envp_exit(t_list *head)
{
	perror_context("malloc", NULL, 2);
	free_envp(head);
	exit(g_current_sig);
}
