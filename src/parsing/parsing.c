/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lefabreg <lefabreg@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 14:00:01 by lefabreg          #+#    #+#             */
/*   Updated: 2024/04/12 06:35:39 by lefabreg         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

typedef struct s_data_q
{
    int index;
    char type;
    int next;
    int match;

} t_data_q;

typedef struct s_quote
{
    char *cmd;
    int sgl_quote;
    int db_quote;
    char type;
    int size;
    char *line;
    struct s_data_q **data;

}   t_quote;

void    check_db(t_quote *quote)
{
    int i;
    
    i = 0;
    quote->size = 0;
    while (quote->cmd[i])
    {
        if (quote->cmd[i] == '"' || quote->cmd[i] == '\'')
            quote->size++;
        i++;
    }
}

void    store_quotes(t_quote *quote)
{
    int i;
    int j;
    
    i = 0;
    j = 0;
    quote->data = malloc(sizeof(t_data_q *) * (quote->size + 1));
    if (!quote->data)
        exit(1);
    quote->data[quote->size] = 0;
    while (quote->cmd[i])
    {
        if (quote->cmd[i] == '"' || quote->cmd[i] == '\'')
        {   
            quote->data[j] = malloc(sizeof(t_data_q) * 1);
            quote->data[j]->index = i;
            quote->data[j]->type = quote->cmd[i];
            quote->data[j]->next = 0;
            quote->data[j]->match = 0;
            j++;
        }
        i++;
    }
}

void display_tab(t_quote *quote)
{
    int count;
    count = 0;

    while (quote->data[count])
    {
        printf("index : %d || type : %c || next : %d\n", quote->data[count]->index, quote->data[count]->type, quote->data[count]->next);
        count++;
    }
}


void    link_quotes(t_quote *quote)
{
    int i;
    int len;
    int j;
    
    len = 0;
    while(quote->data[len])
        len++;
    i = 0;
    while (quote->data[i])
    {
        j = i + 1;
        while (j < (len))
        {
            if ((quote->data[i]->type == quote->data[j]->type) && (!(quote->data[i]->match)))
            {
                quote->data[i]->next = quote->data[j]->index;
                quote->data[j]->match = 1;
                break;
            }
            j++;
        }
        i++;
    }
    printf("%d", quote->data[0]->next);

}

void    quotes_manager(char *command)
{
    t_quote quote;
    
    quote.cmd = command;
    check_db(&quote);
    store_quotes(&quote);
    // display_tab(&quote);
    if (!quote.size)
    {
       printf("%s\n", quote.cmd);
       return ;
    }
    else if (quote.size == 1)
    {
        printf("invalid quotes !\n");
        return ;
    }
    link_quotes(&quote);
    display_tab(&quote);
}

void    parse(char *command)
{
    quotes_manager(command);
}