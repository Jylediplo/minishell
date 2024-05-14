/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_heredocs_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pantoine <pantoine@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 22:33:58 by pantoine          #+#    #+#             */
/*   Updated: 2024/05/14 22:45:55 by pantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execute.h"
#include "../../includes/minishell.h"
#include "../../includes/evars.h"

static int	start_dollar_sequence(int fd, char *input, int *i, t_list *envp)
{
	int		j;
	int		index;
	char	*to_expand;
	char	*expanded;

	*i += 1;
	j = *i;
	index = 0;
	while (valid_identifier_char(input[*i]))
		*i += 1;
	to_expand = malloc(sizeof(char *) * (*i - j + 1));
	if (!to_expand)
	{
		ft_putstr_fd("petitcoq: malloc error\n", 2);
		return (1);
	}
	while (valid_identifier_char(input[j]))
		to_expand[index++] = input[j++];
	to_expand[index] = '\0';
	expanded = get_envvar_value(&envp, to_expand);
	if (expanded)
		write(fd, expanded, ft_strlen(expanded));
	free(to_expand);
	return (0);
}

int	expand_dollars_heredocs(int fd, char *input, t_list *envp, int noexpand)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] == '$' && !noexpand)
			start_dollar_sequence(fd, input, &i, envp);
		else
			write(fd, &input[i++], 1);
	}
	return (0);
}
