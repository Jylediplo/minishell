/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lefabreg <lefabreg@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/25 17:12:25 by jyjy              #+#    #+#             */
/*   Updated: 2024/04/09 16:19:12 by lefabreg         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

size_t	index_for_n(char *buffer)
{
	size_t	i;
	size_t	is_n;

	i = 0;
	is_n = 0;
	if (!buffer)
		return (0);
	while (buffer[i] != '\0')
	{
		if (buffer[i] == '\n')
		{
			is_n = 1;
			i++;
			break ;
		}
		i++;
	}
	if (!is_n)
		return (0);
	return (i);
}
