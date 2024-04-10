/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lefabreg <lefabreg@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 13:45:23 by lefabreg          #+#    #+#             */
/*   Updated: 2024/04/10 13:46:08 by lefabreg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
