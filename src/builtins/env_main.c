/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pantoine <pantoine@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 16:50:06 by pantoine          #+#    #+#             */
/*   Updated: 2024/05/13 22:02:33 by pantoine         ###   ########.fr       */
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
