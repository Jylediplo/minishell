/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lefabreg <lefabreg@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 14:00:01 by lefabreg          #+#    #+#             */
/*   Updated: 2024/04/16 19:31:04 by lefabreg         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

typedef struct s_data_q
{
    int index;
    char type;
    int next;
    int match;
    int size;
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
    struct s_data_q **quote_itv;

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
            quote->data[j]->size = 0;
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
        printf("index : %d || type : %c || next : %d || match %d\n", quote->data[count]->index, quote->data[count]->type, quote->data[count]->next, quote->data[count]->match);
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
}

void create_quot_tab(t_quote *quote)
{
    int i;
    int j;
    int size;
    i = 0;
    j = 0;
    while (quote->data[i])
    {
        if (quote->data[i]->next)
            j++;
        i++;
    }
    quote->quote_itv = malloc(sizeof(t_data_q *) * (j + 1));
    quote->quote_itv[j] = 0;
    size = j;
    i = 0;
    j = 0;
    while(quote->data[i])
    {
        if (quote->data[i]->next)
        {
            quote->quote_itv[j] = malloc(sizeof(t_data_q) * 1);
            quote->quote_itv[j] = quote->data[i];
            quote->quote_itv[j]->size = size;
            j++;
        }
        i++;
    }
}

void check_quotes(t_quote *quote)
{
    int i;
    t_data_q *previous;
    t_data_q  *current;
    t_data_q *next;
    i = 0;
    while (quote->quote_itv[i])
    {
        printf("index : %d || next %d || type : %c \n", 
        quote->quote_itv[i]->index, quote->quote_itv[i]->next, quote->quote_itv[i]->type);
        if ((i >= 1) && (i < (quote->quote_itv[0]->size - 1)))
        {
            previous = quote->quote_itv[i - 1];
            current = quote->quote_itv[i];
            next = quote->quote_itv[i + 1];
            if (((previous->index < current->index) && (next->index > current->index))
            && (current->type != previous->type ) && current->type != next->type)
            {
                printf("oui\n");
            }
        }
        i++;
    }
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
    // else if (quote.size == 1)
    // {
    //     printf("invalid quotes !\n");
    //     return ;
    // }
    link_quotes(&quote);
    //display_tab(&quote);
    create_quot_tab(&quote);
    check_quotes(&quote);
    
}

void    parse(char *command)
{
    quotes_manager(command);
}