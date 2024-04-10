/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_history.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lefabreg <lefabreg@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 12:35:45 by lefabreg          #+#    #+#             */
/*   Updated: 2024/04/10 13:25:49 by lefabreg         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_history_data(void	*data)
{
	t_data_h	*history;

	if (!data)
		return ;
	history = (t_data_h *)data;
	free(history->line);
	free(history);
}

void	handle_history_error(t_list **list)
{
	ft_lstclear(list, free_history_data);
	exit(1);
}

void	ft_lst_display(t_list *lst)
{
	t_list	*current;

	current = lst;
	while (current != NULL)
	{
		printf("%d  ", ((t_data_h *)current->content)->nb);
		printf("%s\n", ((t_data_h *)current->content)->line);
		current = current->next;
	}
}

void    add_to_list(char *command, t_history *history)
{
    (void)command;
    history->data = malloc(sizeof(t_data_h));
    if (!(history->data))
        handle_history_error(&history->list);
    history->size = ft_lstsize(history->list);
    history->data->line = ft_strdup(command);
	if (!history->data->line)
        handle_history_error(&history->list);
	history->data->nb = history->size + 1;
	history->node = ft_lstnew((void *)history->data);
	if (!history->node)
		handle_history_error(&history->list);
	ft_lstadd_back(&history->list, history->node);
}

void    add_to_history(char *command, t_history *history)
{
    int fd;
    
    fd = open(".history", O_APPEND | O_WRONLY);
    if (fd == -1)
        return ;
    write(fd, command, ft_strlen(command));
    write(fd, "\n", 1);
    close(fd);
    add_to_list(command, history);
    add_history(command);
}

void    restore_history(t_history *history)
{
    char    *line;
    char    *word;

    history->fd = open(".history", O_RDONLY);
    if (history->fd == -1)
        perror("fd :");
    line = "init";
    while (line)
    {
        line = get_next_line(history->fd);
        if (line)
        {
            word = ft_strtrim(line, "\n");
            if (!word)
            {
                close(history->fd);
                return(free(line));
            }
            add_to_list(word, history);
            add_history(word);
            free(word);
        }
        free(line);
    }
    close(history->fd);
}