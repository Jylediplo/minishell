/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pantoine <pantoine@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 20:27:44 by pantoine          #+#    #+#             */
/*   Updated: 2024/05/02 13:16:35 by pantoine         ###   ########.fr       */
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
			if (to_echo[i])
				*no_newline = 0;
		}
	}
}

int	efftee_echo(t_shell *shell, char *to_echo)
{
	char	*echo_value;
	int		no_newline;
	t_evar	evar;

	no_newline = 0;
	echo_value = parse_evar(&evar, to_echo, shell->envp);
	if (!echo_value)
		return (1);
	parse_flag(echo_value, &no_newline);
	if (!no_newline)
		printf("%s", echo_value);
	free(echo_value);
	if (evar.set_next && !no_newline)
		printf(" ");
	while (evar.set_next)
	{
		echo_value = parse_evar(&evar, evar.set_next, shell->envp);
		if (!echo_value)
			return (1);
		printf("%s", echo_value);
		if (evar.set_next)
			printf(" ");
		free(echo_value);
	}
	if (!no_newline)
		printf("\n");
	return (0);
}
