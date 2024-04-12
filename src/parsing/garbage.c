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