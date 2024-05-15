/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pantoine <pantoine@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 20:27:44 by pantoine          #+#    #+#             */
/*   Updated: 2024/05/15 14:48:53 by pantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/evars.h"

void	parse_flag(char *to_echo, int *no_newline)
{
	int	i;

	i = 0;
	if (to_echo[i] == '-')
	{
		i++;
		if (to_echo[i++] == 'n')
		{
			*no_newline = 1;
			while (to_echo[i] == 'n')
				i++;
			if (to_echo[i])
				*no_newline = 0;
			return ;
		}
	}
}

void	print_arg(char **cmd, int index, int no_newline)
{
	if (!no_newline && !cmd[index + 1])
		printf("%s\n", cmd[index]);
	else if (no_newline && !cmd[index + 1])
		write(1, cmd[index], ft_strlen(cmd[index]));
	else
		printf("%s ", cmd[index]);
}

int	efftee_echo(char **cmd)
{
	int		no_newline;
	int		len;

	len = 1;
	no_newline = 0;
	while (cmd[len])
	{
		if (len == 1)
		{
			parse_flag(cmd[len], &no_newline);
			if (no_newline)
			{
				len++;
				continue ;
			}
		}
		print_arg(cmd, len, no_newline);
		len++;
	}
	if (len == 1 && !no_newline)
		printf("\n");
	g_current_sig = 0;
	return (0);
}
