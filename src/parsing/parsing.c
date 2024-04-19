/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lefabreg <lefabreg@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 14:00:01 by lefabreg          #+#    #+#             */
/*   Updated: 2024/04/19 19:05:51 by lefabreg         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char *my_strtok(char *s, char *delim) {
    static char *last;
    char *tok;

    if (s == NULL && (s = last) == NULL)
        return NULL;

    while (*s && ft_strchr(delim, *s))
        s++;
// si fin de la string return null
    if (!*s) { 
        last = NULL;
        return (NULL);
    }
    // debut du token ici
    tok = s; 

    // trouve la fin du token
    while (*s && !ft_strchr(delim, *s))
        s++;
//si delimiteur trouve go dans le if
    if (*s)
    { 
        *s = '\0'; 
        last = s + 1; // passe au prochain caractere pour prochain appel
    }
    else 
        last = NULL; // si fin de string, last mis a null
    return (tok);
}

typedef struct s_quote
{
    int input_length;
    int output_index;
    int quote_open;
    int i;
    char current_quote;
    char *output;
} t_quote;

void init_cmd(t_quote *cmd, char *command)
{
    cmd->input_length = (int)ft_strlen(command);
    cmd->i = 0;
    cmd->quote_open = 0;
    cmd->output_index = 0;
    cmd->output = malloc(sizeof(char) * (cmd->input_length + 1));
    if (!cmd->output)
    {
        printf("Memory allocation failed.\n");
        exit(1);
    }
}
void current_is_quote(t_quote *cmd, char *command)
{
    if (!cmd->quote_open)
    {
        cmd->quote_open = 1;
        cmd->current_quote = command[cmd->i];
    }
    else if (cmd->current_quote == command[cmd->i])
        cmd->quote_open = 0;
    else
        cmd->output[cmd->output_index++] = command[cmd->i];
}

void current_is_not_quote(t_quote *cmd, char *command)
{
    if (cmd->quote_open)
        cmd->output[cmd->output_index++] = command[cmd->i];
    else if (command[cmd->i] != ' ')
        cmd->output[cmd->output_index++] = command[cmd->i];
    else
	{
        if (cmd->output_index > 0 && cmd->output[cmd->output_index - 1] != ' ')
            cmd->output[cmd->output_index++] = command[cmd->i];
    }
}

char *manage_quotes(char *command)
{
    t_quote cmd;

    init_cmd(&cmd, command);    
    while (cmd.i < cmd.input_length)
    {
        if (command[cmd.i] == '"' || command[cmd.i] == '\'')
            current_is_quote(&cmd, command);
		else
           current_is_not_quote(&cmd, command);
		cmd.i++;
    }
    if (cmd.quote_open)
    {
        free(cmd.output);
        printf("Error: Quote not properly closed.\n");
        return NULL;
    }
    cmd.output[cmd.output_index] = '\0';
	return (cmd.output);
}

void execute_command(char* command, int input_fd, int output_fd, char **envp) {
    int pid = fork();
    if (pid < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    else if (pid == 0)
    {
        if (input_fd != STDIN_FILENO)
        {
            dup2(input_fd, STDIN_FILENO);
            close(input_fd);
        }
        if (output_fd != STDOUT_FILENO)
        {
            dup2(output_fd, STDOUT_FILENO);
            close(output_fd);
        }
        manage_path(command, envp);
        perror("execve");
        exit(EXIT_FAILURE);
    }
}

#define MAX_COMMANDS 10
#define MAX_ARGS 10

void parse_and_execute(char* input, char **envp)
{
    char* commands[MAX_COMMANDS];
    int num_commands = 0;
    char* token;
    char* delim = "|";
    int i;

    i = 0;
    //tok pour gerer chaque command entre les pipes;
    //a chaque call se decale a la commande apres le pipe
    token = strtok(input, delim);
    while (token != NULL && num_commands < MAX_COMMANDS)
    {
        commands[num_commands++] = token;
        token = strtok(NULL, delim);
    }

    int pipes[MAX_COMMANDS - 1][2];
    while (i < num_commands - 1)
    {
        if (pipe(pipes[i]) == -1)
        {
            perror("pipe");
            exit(EXIT_FAILURE);
        }
        i++;
    }

    i = 0;
    //boucle pour gerer chaque commande avec sses pipes d entree et de sortie
    while (i < num_commands)
    {
        if (i == 0)
        {
            //si premiere commande , stdin mais sortie sera le prochain pipe
            execute_command(commands[i], STDIN_FILENO, pipes[i][1], envp);
        }
        else if (i == num_commands - 1)
        {
            //si derniere commande l entree et le pipe de sortie d avant et la sortie la standard
            execute_command(commands[i], pipes[i - 1][0], STDOUT_FILENO, envp);
        }
        else
        {
            //ici gere toutes les commqndes intermediaires
            execute_command(commands[i], pipes[i - 1][0], pipes[i][1], envp);
        }
        i++;
    }
    i = 0;
    //close les pipes
    while (i < num_commands - 1)
    {
        close(pipes[i][0]);
        close(pipes[i][1]);
        i++;
    }
    // attends to les child process finissent
    i = 0;
    while (i < num_commands)
    {
        wait(NULL);
        i++;
    }
}


void parse(char *command, char **envp)
{
    char *sentence;
	sentence = manage_quotes(command);
   // printf("sentence : %s\n", sentence);
   
    parse_and_execute(sentence, envp);
    free(sentence);
}