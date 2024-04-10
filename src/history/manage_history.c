/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_history.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lefabreg <lefabreg@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 12:35:45 by lefabreg          #+#    #+#             */
/*   Updated: 2024/04/10 12:22:41 by lefabreg         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void    add_to_history(char *command)
{
    int fd;
    
    fd = open(".history", O_APPEND | O_WRONLY);
    if (fd == -1)
        return ;
    write(fd, command, ft_strlen(command));
    write(fd, "\n", 1);
    close(fd);
    add_history(command);
}

void    restore_history(void)
{
    char    *line;
    char    *word;
    int fd;

    fd = open(".history", O_RDONLY);
    if (fd == -1)
        perror("fd :");
    line = "init";
    while (line)
    {
        line = get_next_line(fd);
        if (line)
        {
            word = ft_strtrim(line, "\n");
            if (!word)
            {
                close(fd);
                return(free(line));
            }
            add_history(word);
            free(word);
        }
        free(line);
    }
     close(fd);
}