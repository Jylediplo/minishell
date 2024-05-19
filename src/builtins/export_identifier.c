/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_identifier.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pantoine <pantoine@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 10:47:49 by pantoine          #+#    #+#             */
/*   Updated: 2024/05/19 12:30:56 by pantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/evars.h"

int	valid_identifier_char(char c)
{
	if ((c >= '0' && c <= '9')
		|| (c >= 'a' && c <= 'z')
		|| (c >= 'A' && c <= 'Z')
		|| c == '_')
		return (1);
	return (0);
}

static int	valid_identifier(char *identifier, char operator)
{
	int	i;

	i = 0;
	if ((identifier[i] >= '0' && identifier[i] <= '9')
		|| identifier[i] == operator)
		return (0);
	while (identifier[i])
	{
		if (identifier[i] == operator)
			break ;
		if (!valid_identifier_char(identifier[i++]))
			return (0);
	}
	if (identifier[i] == operator && operator == '+')
	{
		i++;
		if (identifier[i] != '=')
			return (0);
	}
	return (1);
}

int	get_next_operator(t_evar *evar, char *parsed_command)
{
	evar->s_change_evar.plus_str = NULL;
	evar->s_change_evar.equal_str = NULL;
	evar->s_change_evar.append = 0;
	evar->s_change_evar.plus_str = ft_strchr(parsed_command, '+');
	evar->s_change_evar.equal_str = ft_strchr(parsed_command, '=');
	if ((!evar->s_change_evar.plus_str && evar->s_change_evar.equal_str)
		|| (evar->s_change_evar.plus_str > evar->s_change_evar.equal_str
			&& evar->s_change_evar.equal_str))
		evar->s_change_evar.operator = '=';
	else if ((evar->s_change_evar.plus_str < evar->s_change_evar.equal_str)
		&& evar->s_change_evar.equal_str)
		evar->s_change_evar.operator = '+';
	else if (evar->s_change_evar.plus_str && !evar->s_change_evar.equal_str)
	{
		set_err_status(evar, INVALID_IDENTIFIER);
		evar->s_change_evar.operator = '\0';
		return (1);
	}
	else
		evar->s_change_evar.operator = '\0';
	return (0);
}

int	init_change_evar(t_shell *shell, t_evar *evar, char *parsed_command)
{
	if (get_next_operator(evar, parsed_command))
	{
		evar_error_message(evar, parsed_command);
		return (1);
	}
	else if (evar->s_change_evar.operator)
	{
		if (evar->s_change_evar.operator == '+')
			evar->s_change_evar.append = 1;
		if (valid_identifier(parsed_command, evar->s_change_evar.operator))
		{
			add_to_envp(shell, evar, parsed_command);
			return (0);
		}
		else
		{
			set_err_status(evar, INVALID_IDENTIFIER);
			evar_error_message(evar, parsed_command);
		}
	}
	return (1);
}
