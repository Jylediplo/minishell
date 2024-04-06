/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lefabreg <lefabreg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 14:44:56 by pantoine          #+#    #+#             */
/*   Updated: 2024/04/06 17:31:26 by lefabreg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
//readline
#include <readline/readline.h>
//history
#include <readline/history.h>
//signal
#include <signal.h>
//basic i/o
#include <unistd.h>
//libft
#include "../libft/libft.h"

///functions prototype
//signals
extern int	current_sig;
void		handle_signals(void);
//history
void		manage_history(char	*command);

#endif
