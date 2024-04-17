/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lefabreg <lefabreg@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 14:00:01 by lefabreg          #+#    #+#             */
/*   Updated: 2024/04/17 18:48:56 by lefabreg         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void    quotes_manager(char *command)
{
    int i;
    int j;

    j = 0;
    i = 0;
    while (command[i])
    {
        command = strchr(command, '\"');
        if (command)
            printf("%c", command[i]);
        else
        {
            printf("%c", command[i]);
        }
        i++;
    }
}

void    parse(char *command)
{
    quotes_manager(command);
}