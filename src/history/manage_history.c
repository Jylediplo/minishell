/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_history.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lefabreg <lefabreg@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 17:29:39 by lefabreg          #+#    #+#             */
/*   Updated: 2024/04/07 17:34:34 by lefabreg         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_history_data(void	*data)
{
	t_history	*history;

	if (!data)
		return ;
	history = (t_history *)data;
	free(history->line);
	free(history);
}

void	ft_lst_display(t_list *lst)
{
	t_list	*current;

	current = lst;
	while (current != NULL)
	{
		printf("%d  ", ((t_history *)current->content)->nb);
		printf("%s\n", ((t_history *)current->content)->line);
		current = current->next;
	}
}

void	handle_history_error(t_list **list)
{
	ft_lstclear(list, free_history_data);
	exit(1);
}
//test pour git 1
void	manage_history(char *command, t_list **list)
{
	t_history	*data;
	t_list		*node;
	int			size;

	add_history(command);
	data = malloc(sizeof(t_history));
	if (!data)
		handle_history_error(list);
	size = ft_lstsize(*list);
	data->line = ft_strdup(command);
	if (!data->line)
		handle_history_error(list);
	data->nb = size + 1;
	node = ft_lstnew((void *)data);
	if (!node)
		handle_history_error(list);
	ft_lstadd_back(list, node);
	return ;
}
