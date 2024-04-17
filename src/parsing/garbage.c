// typedef struct s_quotes
// {
//     int index_quot;
//     char quote;
//     char *command;
//     char *line_to_print;
// 	char	*inside_quote;
// 	int cursor;
// } t_quotes;

// void find_quots(t_quotes *quotes)
// {

//     while(*quotes->command && *quotes->command != '\0')
//     {
//         if (*quotes->command == '\'' || *quotes->command == '"')
//         {
//             quotes->quote = *quotes->command;
//             return ;
//         }
//         quotes->command++;
//         quotes->index_quot += 1;
//     }
//     //if no quotes have been found, then index and quote set to null;
//     quotes->index_quot = 0;
//     quotes->quote = 0;
// }

// int find_next_quote(t_quotes *quotes)
// {
// 	int i;
// 	int count;

// 	count = 0;
// 	i = quotes->cursor + 1;
// 	printf("quotes cursor : %d\n", i);
// 	printf("command : %s\n", quotes->command);
// 	while(quotes->command[i] != '\0')
// 	{
// 		printf("value : %c\n", quotes->command[i]);
// 		if (quotes->command[i] == quotes->quote)s
// 			return (count);
// 		i++;
// 		count++;
// 	}
// 	return (0);
// }

// void quotes_manager(char *command)
// {
//     t_quotes quotes;

//     quotes.command = command;
//     quotes.index_quot = 0;
//     find_quots(&quotes);
//     //printf("quotes : %c && index : %d\n", quotes.quote, quotes.index_quot);
//     if(!quotes.quote)
//         quotes.line_to_print = command;
//     else
// 	{
// 		quotes.cursor = quotes.index_quot;
//         quotes.line_to_print = ft_substr(command, 0, quotes.index_quot);
// 	}

// 	//printf("line to print : %s\n", quotes.line_to_print);
// 	int len_inside = find_next_quote(&quotes);
// 	(void)len_inside;
// 	// quotes.inside_quote = ft_substr(command, quotes.cursor, len_inside);
// 	// printf("inside quote : %s\n", quotes.inside_quote);
//    //find the next closing parenthesis

    
// }


// typedef struct s_data_q
// {
//     int index;
//     char type;
//     int next;
//     int match;
//     int size;
//     int surrounded;
// } t_data_q;

// typedef struct s_quote
// {
//     char *cmd;
//     int sgl_quote;
//     int db_quote;
//     char type;
//     int size;
//     char *line;
//     struct s_data_q **data;
//     struct s_data_q **quote_itv;

// }   t_quote;

// void    check_db(t_quote *quote)
// {
//     int i;
    
//     i = 0;
//     quote->size = 0;
//     while (quote->cmd[i])
//     {
//         if (quote->cmd[i] == '"' || quote->cmd[i] == '\'')
//             quote->size++;
//         i++;
//     }
// }

// void    store_quotes(t_quote *quote)
// {
//     int i;
//     int j;
    
//     i = 0;
//     j = 0;
//     quote->data = malloc(sizeof(t_data_q *) * (quote->size + 1));
//     if (!quote->data)
//         exit(1);
//     quote->data[quote->size] = 0;
//     while (quote->cmd[i])
//     {
//         if (quote->cmd[i] == '"' || quote->cmd[i] == '\'')
//         {   
//             quote->data[j] = malloc(sizeof(t_data_q) * 1);
//             quote->data[j]->index = i;
//             quote->data[j]->type = quote->cmd[i];
//             quote->data[j]->next = 0;
//             quote->data[j]->match = 0;
//             quote->data[j]->size = 0;
//             quote->data[j]->surrounded = 0;
//             j++;
//         }
//         i++;
//     }
// }

// void display_tab(t_quote *quote)
// {
//     int count;
//     count = 0;

//     while (quote->data[count])
//     {
//         printf("index : %d || type : %c || next : %d || match %d\n", quote->data[count]->index, quote->data[count]->type, quote->data[count]->next, quote->data[count]->match);
//         count++;
//     }
// }


// void    link_quotes(t_quote *quote)
// {
//     int i;
//     int len;
//     int j;
    
//     len = 0;
//     while(quote->data[len])
//         len++;
//     i = 0;
//     while (quote->data[i])
//     {
//         j = i + 1;
//         while (j < (len))
//         {
//             if ((quote->data[i]->type == quote->data[j]->type) && (!(quote->data[i]->match)))
//             {
//                 quote->data[i]->next = quote->data[j]->index;
//                 quote->data[j]->match = 1;
//                 break;
//             }
//             j++;
//         }
//         i++;
//     }
// }

// void create_quot_tab(t_quote *quote)
// {
//     int i;
//     int j;
//     int size;
//     i = 0;
//     j = 0;
//     while (quote->data[i])
//     {
//         if (quote->data[i]->next)
//             j++;
//         i++;
//     }
//     quote->quote_itv = malloc(sizeof(t_data_q *) * (j + 1));
//     quote->quote_itv[j] = 0;
//     size = j;
//     i = 0;
//     j = 0;
//     while(quote->data[i])
//     {
//         if (quote->data[i]->next)
//         {
//             quote->quote_itv[j] = malloc(sizeof(t_data_q) * 1);
//             quote->quote_itv[j] = quote->data[i];
//             quote->quote_itv[j]->size = size;
//             j++;
//         }
//         i++;
//     }
// }

// void print_sentence(char  *line, int begin, int end)
// {
//     int i;

//     i = 0;
//     while (line[i])
//     {
//         if ((i > begin) && (i < end))
//         {
//             printf("%c", line[i]);
//         }
//         i++;
//     }
// }

// void print_quott(t_quote *quote)
// {
//     int i;

//     i = 0;
//     while(quote->quote_itv[i])
//     {
//          printf("index : %d || next %d || type : %c || surrounded : %d\n", 
//         quote->quote_itv[i]->index, quote->quote_itv[i]->next, quote->quote_itv[i]->type,
//         quote->quote_itv[i]->surrounded);
//         // if (quote->quote_itv[i]->surrounded == 0)
//         // {
//         //     if (i == 0 && quote->quote_itv[i]->index)
//         //     {
//         //         print_sentence(quote->cmd, -1, quote->quote_itv[i]->index);   
//         //     }
//         //     print_sentence(quote->cmd, quote->quote_itv[i]->index, quote->quote_itv[i]->next);
//         // }
//         // else if (i < (quote->quote_itv[0]->size - 1))
//         // {
//         //     print_sentence(quote->cmd, (quote->quote_itv[i - 1]->next), quote->quote_itv[i + 1]->index);
//         // }
//         // if (i < quote->quote_itv[0]->size - 1)
//         // {
//         // if (quote->quote_itv[i]->next < quote->quote_itv[i + 1]->index)
//         // {
//         //         print_sentence(quote->cmd, quote->quote_itv[i]->next, quote->quote_itv[i + 1]->index);
//         // }
//         // }
//         // if (i == (quote->quote_itv[0]->size - 1) && quote->quote_itv[i]->next < (int)ft_strlen(quote->cmd) && (quote->quote_itv[i]->surrounded == 0))
//         // {
//         //      print_sentence(quote->cmd, quote->quote_itv[i]->next, (int)ft_strlen(quote->cmd));
//         // }
//          i++;
//     }
//     printf("\n");
// }

// void check_quotes(t_quote *quote)
// {
//     int i;
//     t_data_q *previous;
//     t_data_q  *current;
//     t_data_q *next;

//     i = 0;
//     while (quote->quote_itv[i])
//     {
//         // printf("index : %d || next %d || type : %c \n", 
//         // quote->quote_itv[i]->index, quote->quote_itv[i]->next, quote->quote_itv[i]->type);
//         if ((i >= 1) && (i < (quote->quote_itv[0]->size)))
//         {
//             previous = quote->quote_itv[i - 1];
//             current = quote->quote_itv[i];
//             next = quote->quote_itv[i + 1];
            
//             if (((previous->next > current->index) && (current->type != previous->type )) 
//                 && (!previous->surrounded))
//             {
//                 //printf("oui\n");
//                 current->surrounded = 1;
//             }
//         }
//         i++;
//     }
// }

// void    quotes_manager(char *command)
// {
//     t_quote quote;
    
//     quote.cmd = command;
//     check_db(&quote);
//     store_quotes(&quote);
//     // display_tab(&quote);
//     if (!quote.size)
//     {
//        printf("%s\n", quote.cmd);
//        return ;
//     }
//     // else if (quote.size == 1)
//     // {
//     //     printf("invalid quotes !\n");
//     //     return ;
//     // }
//     link_quotes(&quote);
//     //display_tab(&quote);
//     create_quot_tab(&quote);
//     check_quotes(&quote);
//     print_quott(&quote);
// }