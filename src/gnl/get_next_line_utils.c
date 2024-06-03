/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lefabreg <lefabreg@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 13:45:23 by lefabreg          #+#    #+#             */
/*   Updated: 2024/06/03 13:26:18 by pantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_eof(char *buffer, int bytes_read)
{
	int	i;

	i = 0;
	while (i < bytes_read)
	{
		if (buffer[i] == 28)
			i++;
		else if (buffer[i] != 28)
			return (0);
	}
	return (1);
}

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
