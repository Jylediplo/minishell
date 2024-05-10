/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lefabreg <lefabreg@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 14:00:01 by lefabreg          #+#    #+#             */
/*   Updated: 2024/05/10 23:12:49 by lefabreg         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */


// char *my_strtok(char *s, char *delim) {
//     static char *last;
//     char *tok;

//     if (s == NULL && (s = last) == NULL)
//         return NULL;

//     while (*s && ft_strchr(delim, *s))
//         s++;
// // si fin de la string return null
//     if (!*s) { 
//         last = NULL;
//         return (NULL);
//     }
//     // debut du token ici
//     tok = s; 

//     // trouve la fin du token
//     while (*s && !ft_strchr(delim, *s))
//         s++;
// //si delimiteur trouve go dans le if
//     if (*s)
//     { 
//         *s = '\0'; 
//         last = s + 1; // passe au prochain caractere pour prochain appel
//     }
//     else 
//         last = NULL; // si fin de string, last mis a null
//     return (tok);
// }

// typedef struct s_lexer
// {
// 	int index;
// 	//check for builtins
// 	enum
// 	{
// 		NONE = 258,
// 		WORD = 259,
// 		PIPE = 260,
// 		GREATER = 261,
// 	}	flag;
// 	char *word;

// } t_lexer;

// typedef struct s_quote
// {
//     int input_length;
//     int output_index;
//     int quote_open;
//     int i;
//     char current_quote;
//     char **words; // Array to hold words
// 	t_lexer **lexer;
//     int word_count; // Number of words
//     char *current_word; // Temporary storage for the current word
// } t_quote;

// void init_cmd(t_quote *cmd, char *command)
// {
//     cmd->input_length = (int)strlen(command);
//     cmd->i = 0;
//     cmd->quote_open = 0;
//     cmd->output_index = 0;
//     cmd->words = NULL;
//     cmd->word_count = 0;
//     cmd->current_word = NULL;
// 	cmd->lexer = NULL;
// }

// void current_is_quote(t_quote *cmd, char *command)
// {
//     if (!cmd->quote_open)
//     {
//         cmd->quote_open = 1;
//         cmd->current_quote = command[cmd->i];
//     }
//     else if (cmd->current_quote == command[cmd->i])
//         cmd->quote_open = 0;
//     else
//         cmd->current_word[cmd->output_index++] = command[cmd->i];
// }

// void current_is_not_quote(t_quote *cmd, char *command)
// {
//     if (cmd->quote_open)
//     {
//         cmd->current_word[cmd->output_index++] = command[cmd->i];
//     }
//     else if (command[cmd->i] != ' ')
//     {
//         cmd->current_word[cmd->output_index++] = command[cmd->i];
//     }
//     else
//     {
//         if (cmd->output_index > 0)
//         {
//             cmd->current_word[cmd->output_index] = '\0'; // Null-terminate the word
//             cmd->words = realloc(cmd->words, (cmd->word_count + 1) * sizeof(char *));
//             cmd->words[cmd->word_count++] = cmd->current_word;
//             cmd->current_word = NULL;
//             cmd->output_index = 0;
//         }
//     }
// }

// char **manage_quotes(char *command)
// {
//     t_quote cmd;
	
//     init_cmd(&cmd, command);
//     while (cmd.i < cmd.input_length)
//     {
//         if (command[cmd.i] == '"' || command[cmd.i] == '\'')
//             current_is_quote(&cmd, command);
//         else
//         {
//             if (!cmd.current_word)
//                 cmd.current_word = malloc((cmd.input_length + 1) * sizeof(char)); // Allocate space for the word
//             current_is_not_quote(&cmd, command);
//         }
//         cmd.i++;
//     }
//     if (cmd.quote_open)
//         return (printf("Error: Quote not properly closed.\n"), NULL);
//     if (cmd.current_word)
//     {
//         cmd.current_word[cmd.output_index] = '\0';
//         cmd.words = realloc(cmd.words, (cmd.word_count + 1) * sizeof(char *));
//         cmd.words[cmd.word_count++] = cmd.current_word;
//     }
//     cmd.words = realloc(cmd.words, (cmd.word_count + 1) * sizeof(char *));
//     return (cmd.words[cmd.word_count] = NULL, cmd.words);
// }

// void parse(char *command, char **envp)
// {
//     (void)envp;
// 	int i;
	
// 	i = 0;
//     char **sentence;
// 	sentence = manage_quotes(command);
// 	if (!sentence)
// 		return ;
// 	while (sentence[i])
// 	{
//     	printf("sentence : %s\n", sentence[i]);
// 		free(sentence[i]);
// 		i++;
// 	}
//     // parse_and_execute(sentence, envp);
//     // printf("ended properly\n");
//     free(sentence);
//}
