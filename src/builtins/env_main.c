/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pantoine <pantoine@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 16:50:06 by pantoine          #+#    #+#             */
/*   Updated: 2024/05/26 17:23:21 by pantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/evars.h"

int	show_me_the_way(t_list *envp)
{
	t_list	*iter;

	iter = envp;
	while (iter)
	{
		printf("%s\n", (char *)iter->content);
		iter = iter->next;
	}
	return (1);
}
