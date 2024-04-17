/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyjy <jyjy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 14:00:01 by lefabreg          #+#    #+#             */
/*   Updated: 2024/04/18 00:43:58 by jyjy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


void  manage_quotes(char *command)
{

    int input_length = (int)ft_strlen(command);
    int output_index = 0;
    int quote_open = 0;
	int i;
    char current_quote;

    char* output = (char*)malloc(1000 * sizeof(char));
    if (output == NULL)
	{
        printf("Memory allocation failed.\n");
        exit(1);
    }
	i = 0;
    while (i < input_length) {
        if (command[i] == '"' || command[i] == '\'') {
            if (!quote_open)
			{
                quote_open = 1;
                current_quote = command[i];
            } else if (current_quote == command[i])
			{
                quote_open = 0;
            } else
			{
                output[output_index++] = command[i];
            }
        }
		else
		{
            if (quote_open)
			{
                output[output_index++] = command[i];
            } else if (command[i] != ' ')
			{
				output[output_index++] = command[i];
			}else
			{
            	if (output_index > 0 && output[output_index - 1] != ' ')
				{
                    output[output_index++] = command[i];
            	}
            }
        }
		i++;
    }
    if (quote_open) {
        printf("Error: Quote not properly closed.\n");
        return ;
    }
    output[output_index] = '\0';
    printf("commmand : %s\n", output);
	free(output);
}

void parse(char *command)
{
	manage_quotes(command);
}
