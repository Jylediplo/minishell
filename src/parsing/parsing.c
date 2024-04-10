/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lefabreg <lefabreg@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 14:00:01 by lefabreg          #+#    #+#             */
/*   Updated: 2024/04/10 18:14:54 by lefabreg         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int length_between_quotes(char *start, char quote)
{
    int count;

    count = 0;
    while(*start)
    {
        if (*start == quote)
            return (count);
        start++;
        count++;
    }
    return (0);
}

void quotes_manager(char *command)
{
    char    *trim;
    char    *start;
    int     char_between;
    char    *word;
    
    trim = strchr(command, '"');
    if (trim)
        start = ++trim;
    else
    {
        printf("no words detected\n");
        return ;
    }
    char_between = length_between_quotes(start, '"');
    word = ft_substr(start, 0, char_between);
    free(trim);
    // sequence
    
    printf("word:  %s\n", word);
}

void    parse(char *command)
{
    quotes_manager(command);
}