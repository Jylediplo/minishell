/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pantoine <pantoine@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 20:55:25 by pantoine          #+#    #+#             */
/*   Updated: 2024/05/13 22:51:08 by pantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/evars.h"
#include "../../includes/execute.h"

void	get_pwd(void)
{
	char	path[4096];

	if (!getcwd(path, 4096))
		perror_context("getcwd", NULL);
	else
		printf("%s\n", path);
}
