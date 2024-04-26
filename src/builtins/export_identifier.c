/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_identifier.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pantoine <pantoine@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 10:47:49 by pantoine          #+#    #+#             */
/*   Updated: 2024/04/26 14:46:55 by pantoine         ###   ########.fr       */
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

int	valid_identifier(char *identifier, char operator)
{
	if ((*identifier >= '0' && *identifier <= '9')
		|| *identifier == operator)
		return (0);
	while (*identifier && *identifier != operator)
	{
		if (!valid_identifier_char(*identifier++))
			return (0);
	}
	return (1);
}

int	get_next_operator(t_evar *evar, char *parsed_command)
{
	evar->change_evar.plus_str = NULL;
	evar->change_evar.equal_str = NULL;
	evar->change_evar.append = 0;
	evar->change_evar.plus_str = ft_strchr(parsed_command, '+');
	evar->change_evar.equal_str = ft_strchr(parsed_command, '=');
	if ((!evar->change_evar.plus_str && evar->change_evar.equal_str)
		|| (evar->change_evar.plus_str > evar->change_evar.equal_str
			&& evar->change_evar.equal_str))
		evar->change_evar.operator = '=';
	else if ((evar->change_evar.plus_str < evar->change_evar.equal_str)
		&& evar->change_evar.equal_str)
		evar->change_evar.operator = '+';
	else if (evar->change_evar.plus_str && !evar->change_evar.equal_str)
	{
		set_err_status(evar, INVALID_IDENTIFIER);
		evar->change_evar.operator = '\0';
		return (1);
	}
	else
		evar->change_evar.operator = '\0';
	return (0);
}

void	init_change_evar(t_evar *evar, char *parsed_command)
{
	if (!parsed_command)
		return ;
	printf("Parsed command: <%s>\n", parsed_command);
	if (get_next_operator(evar, parsed_command))
	{
		evar_error_message(evar);
		return ;
	}
	if (evar->change_evar.operator)
	{
		if (evar->change_evar.operator == '+')
			evar->change_evar.append = 1;
		if (valid_identifier(parsed_command, evar->change_evar.operator))
			printf("valid\n");
		else
			printf("invalid\n");
	}
	else
		printf("No operators detected !! This variable will be added to envp, but typing 'env' will not show it. You can access see it with 'echo'.\n");
}
