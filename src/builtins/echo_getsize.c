/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_getsize.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pantoine <pantoine@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 11:03:48 by pantoine          #+#    #+#             */
/*   Updated: 2024/05/28 16:40:40 by pantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/evars.h"

static char	*parse_quoted_sequence_echo(t_evar *evar,
											char quotetype, t_list *envp)
{
	if (!ft_strchr(evar->newvalue + 1, quotetype))
		return (set_err_status(evar, UNCLOSED_QUOTE), NULL);
	while (*evar->newvalue != quotetype && evar->e_error != BAD_SUBSTITUTION)
	{
		if (*evar->newvalue == '$')
			size_dol_substitution(evar, 0, envp);
		else
			increase_size_evar(evar);
	}
	evar->newvalue++;
	while (*evar->newvalue != quotetype
		&& evar->e_error != BAD_SUBSTITUTION
		&& evar->e_error != MALLOC)
	{
		if (*evar->newvalue == '$' && quotetype == '\"')
			size_dol_substitution(evar, 1, envp);
		else
			increase_size_evar(evar);
	}
	if (*evar->newvalue)
		evar->newvalue += 1;
	return (evar->newvalue);
}

void	get_echo_size(t_evar *evar, t_list *envp)
{
	while (*evar->newvalue)
	{
		get_next_quotetype(evar);
		if (evar->quotetype)
			evar->newvalue = parse_quoted_sequence_echo(evar,
					evar->quotetype, envp);
		else if (!evar->quotetype)
		{
			if (*evar->newvalue == '$')
				size_dol_substitution(evar, 0, envp);
			else
				increase_size_evar(evar);
		}
		if (evar->e_error == BAD_SUBSTITUTION
			|| evar->e_error == MALLOC
			|| !evar->newvalue)
			return ;
		find_next_quotes(evar, evar->newvalue, 0);
	}
}

char	*parse_echo(t_list *envp, char *to_echo, int fd)
{
	t_evar	evar;

	init_evar(&evar, to_echo, envp);
	if (evar.e_error != NONE)
	{
		evar_error_message(&evar, NULL, fd);
		return (NULL);
	}
	evar.e_error = NONE;
	evar.newvalue_copy = ft_strdup(to_echo);
	if (!evar.newvalue_copy)
	{
		perror_context("malloc", NULL, fd);
		return (NULL);
	}
	evar.newvalue_toset = malloc(sizeof(char) * (evar.size_evar + 1));
	if (!evar.newvalue_toset)
	{
		perror_context("malloc", NULL, fd);
		free(evar.newvalue_copy);
		return (NULL);
	}
	get_echo(&evar, envp, fd);
	free(evar.newvalue_copy);
	return (evar.newvalue_toset);
}
