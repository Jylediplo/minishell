/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_history.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lefabreg <lefabreg@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 17:29:39 by lefabreg          #+#    #+#             */
/*   Updated: 2024/04/07 13:30:10 by lefabreg         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_history_data(void	*data)
{
	t_history *history;
	
	if (!data)
		return;
	history = (t_history *)data;
	free(history->line);
	free(history);
}

void	ft_lst_display(t_list *lst)
{
	t_list *current = lst;
    while (current != NULL)
	{
        printf("%d  ", ((t_history *)current->content)->nb);
        printf("%s\n", ((t_history *)current->content)->line);
        current = current->next;
    }
}

void	manage_history(char	*command, t_list **list)
{
	t_history	*data;
	t_list		*node;
	int size;
	
	add_history(command);
	data = malloc(sizeof(t_history));
	if (!data)
	{
		exit(1);
	}
	size = ft_lstsize(*list);
	data->line  = ft_strdup(command);
	data->nb = size + 1;
	node = ft_lstnew((void *)data);
	ft_lstadd_back(list, node);
	return ;
}