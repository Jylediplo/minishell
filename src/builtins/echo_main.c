/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pantoine <pantoine@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 20:27:44 by pantoine          #+#    #+#             */
/*   Updated: 2024/05/06 19:06:14 by pantoine         ###   ########.fr       */
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

int	efftee_echo(t_shell *shell, char *to_echo)
{
	char	*echo_value;
	int		no_newline;
	int		next_flags_newline;
	t_evar	evar;

	no_newline = 0;
	next_flags_newline = 0;
	echo_value = parse_evar(&evar, to_echo, shell->envp);
	if (!echo_value)
		return (1);
	parse_flag(echo_value, &no_newline);
	if (!no_newline)
		printf("%s", echo_value);
	free(echo_value);
	if (evar.set_next && !no_newline)
		printf(" ");
	echo_next_args(&evar, echo_value, next_flags_newline, shell->envp);
	if (!no_newline)
		printf("\n");
	return (0);
}
