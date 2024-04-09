/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_history.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lefabreg <lefabreg@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 12:35:45 by lefabreg          #+#    #+#             */
/*   Updated: 2024/04/09 18:58:56 by lefabreg         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void    restore_history(void)
{
    char    *line;
    int fd;

    fd = open(".history", O_RDONLY);
    if (fd == -1)
        perror("fd :");
    line = get_next_line(fd);
    printf("")
}