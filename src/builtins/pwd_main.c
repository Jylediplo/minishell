/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pantoine <pantoine@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 20:55:25 by pantoine          #+#    #+#             */
/*   Updated: 2024/05/26 18:13:26 by pantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/evars.h"
#include "../../includes/execute.h"

void	get_pwd(void)
{
	char	path[4096];

	if (!getcwd(path, 4096))
	{
		perror_context("getcwd", NULL);
		g_current_sig = 1;
	}
	else
		printf("%s\n", path);
}
