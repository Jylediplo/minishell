/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_tests.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pantoine <pantoine@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 11:57:43 by pantoine          #+#    #+#             */
/*   Updated: 2024/04/20 15:22:32 by pantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPORT_TESTS_H
# define EXPORT_TESTS_H

#include "../includes/evars.h"
#include <fcntl.h>
#include <unistd.h>

char	*get_next_line(int fd);
int		test_export(t_shell *shell, char *(*parser)(t_shell *, char *));

#endif
