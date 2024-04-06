/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pantoine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 18:00:19 by pantoine          #+#    #+#             */
/*   Updated: 2023/11/17 10:51:01 by pantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*nextn;

	if (*lst == NULL)
		return ;
	while (*lst)
	{
		nextn = (*lst)->next;
		ft_lstdelone(*lst, del);
		*lst = nextn;
	}
	*lst = NULL;
}
