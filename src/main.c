/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lefabreg <lefabreg@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 02:28:18 by lefabreg          #+#    #+#             */
/*   Updated: 2024/04/06 02:28:18 by lefabreg         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int  main(void)
{
    char    *command;

    while (1)
    {
    command = readline("Super prompt > ");
    printf("command : %s \n", command);
    free(command);
    }
    return (0);
}


char tab[2][10] = {"EXPORT", "EXIT"};