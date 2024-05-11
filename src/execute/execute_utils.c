/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pantoine <pantoine@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 21:00:14 by pantoine          #+#    #+#             */
/*   Updated: 2024/05/11 21:04:44 by pantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execute.h"
#include "../../includes/evars.h"
#include "../../includes/minishell.h"

int	flag_redirect_stream(t_lexer **lexer, int *lexer_pos)
{
	if (lexer[*lexer_pos]->flag == APPEND
		|| lexer[*lexer_pos]->flag == GREATER
		|| lexer[*lexer_pos]->flag == LESSER)
		return (1);
	return (0);
}

int	flag_add_to_node(t_lexer **lexer, int *lexer_pos)
{
	if (lexer[*lexer_pos]->flag == WORD
		|| lexer[*lexer_pos]->flag == PIPE
		|| lexer[*lexer_pos]->flag == BUILTIN)
		return (1);
	return (0);
}
