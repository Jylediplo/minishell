/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lefabreg <lefabreg@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 14:00:01 by lefabreg          #+#    #+#             */
/*   Updated: 2024/04/18 18:45:18 by lefabreg         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


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
   // printf("commmand : %s\n", cmd.output);
	return (cmd.output);
}

typedef struct s_d
{
    int index;
    char **cmd;
} t_d;

typedef struct s_cmd
{
    t_list  *list;
    t_list  *node;
    int size;
    t_d   *data;
}   t_cmd;

void add_data(t_cmd *cmds, int index, char **split)
{
    int i;
    i = 0;
    
    int j;
    j = 0;
    cmds->data->cmd = malloc(sizeof(char *) * (index + 1));
    cmds->data->index = 0;
    while (i < index)
    {
        cmds->data->cmd[i] = malloc(sizeof(char) * (ft_strlen(split[i]) + 1));
        cmds->data->cmd[i] = split[i];
        i++;
    }
}

void handle_cmd(char **split, t_cmd *cmds)
{
    int i;
    int index_previous;

    index_previous = 0;
    i = 0;
    while (split[i])
    {
        if (!ft_strncmp(split[i], "|", 1))
        {
            if (i == (cmds->size - 1))
                printf("invalid |\n");
            printf("here\n");
            if (!index_previous)
            {
                //create node;
                // cmds->data = malloc(sizeof(t_d));
                // add_data(cmds, i, split);
                // cmds->node = ft_lstnew((void *)cmds->data);
                // char **index;
                // index = ((t_d *)cmds->node->content)->cmd;
                index_previous = i;
            }
            else
            {
                
            }
        }
        i++;
    }
}

void parse(char *command)
{
    char *sentence;
    char **split;
    t_cmd cmds;
    int i;

    i = 0;
    cmds.list = NULL;
	sentence = manage_quotes(command);
   // printf("command : %s\n", sentence);
    split = ft_split(sentence, ' ');
    free(sentence);
    while(split[i])
        i++;
    cmds.size = i;
    handle_cmd(split, &cmds);
}
//grep "  "
//char *
// ls -la | grep " "
//[ls] [-la]
// [grep] [32]