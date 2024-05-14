/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pantoine <pantoine@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 20:27:44 by pantoine          #+#    #+#             */
/*   Updated: 2024/05/14 15:51:12 by pantoine         ###   ########.fr       */
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

int	echo_next_args(t_evar *evar, char *echo_value,
					int next_flags_newline, t_list *envp)
{
	while (evar->set_next)
	{
		echo_value = parse_evar(evar, evar->set_next, envp);
		if (!echo_value)
			return (1);
		parse_flag(echo_value, &next_flags_newline);
		if (!next_flags_newline)
			printf("%s", echo_value);
		if (evar->set_next && !next_flags_newline)
			printf(" ");
		free(echo_value);
	}
	return (0);
}

void	print_arg(char **cmd, int index, int no_newline)
{
	if (!no_newline && !cmd[index + 1])
		printf("%s\n", cmd[index]);
	else if (no_newline && !cmd[index + 1])
		printf("%s", cmd[index]);
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
	return (0);
}
