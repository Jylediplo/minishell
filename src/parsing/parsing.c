/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lefabreg <lefabreg@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 14:00:01 by lefabreg          #+#    #+#             */
/*   Updated: 2024/04/12 03:46:52 by lefabreg         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

typedef struct s_data_q
{
    int index;
    char type;

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
        printf("index : %d || type : %c\n", quote->data[count]->index, quote->data[count]->type);
        count++;
    }
}


void    build_sentence(t_quote *quote)
{
   // int i;
    char *line;
   // i = 0;

    // while (quote->data[i])
    // {
    //     line = ft_substr(quote->cmd, i, quote->data[i]->index);
    //     break;
    // }
    int len = quote->data[1]->index - quote->data[0]->index;
    line = ft_substr(quote->cmd, quote->data[0]->index += 1, len);
    printf("line : %s\n", line);
}

void    quotes_manager(char *command)
{
    t_quote quote;
    
    quote.cmd = command;
    check_db(&quote);
    store_quotes(&quote);
    display_tab(&quote);
    //printf("line : %s\n", quote.cmd);
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
    build_sentence(&quote);
}

void    parse(char *command)
{
    quotes_manager(command);
}