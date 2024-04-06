/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pantoine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 11:49:57 by pantoine          #+#    #+#             */
/*   Updated: 2023/11/17 13:29:25 by pantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*res;
	t_list	*iter;
	void	*tcontent;

	if (!lst || !f)
		return (NULL);
	res = NULL;
	while (lst)
	{
		tcontent = f(lst->content);
		iter = ft_lstnew(tcontent);
		if (!iter)
		{
			free(tcontent);
			ft_lstclear(&res, del);
			return (NULL);
		}
		ft_lstadd_back(&res, iter);
		lst = lst->next;
	}
	return (res);
}
/*
void	*addOne(void * p) {void * r = malloc(sizeof(int));
	 *(int*)r = *(int*)p + 1; return (r);}
void	freeList(t_list *head) {if (head) freeList((t_list *)head->next);
	free(head);}

int	main(void)
{	
	t_list	*l;
	t_list	*l1;
	t_list	*l2;
	t_list	*l3;
	t_list	*test;

	l = ft_lstnew((void *)"ok");
	l1 = ft_lstnew((void *)"okk");
	l2 = ft_lstnew((void *)"okkk");
	l3 = ft_lstnew((void *)"okkkk");
	ft_lstadd_back(&l, l1);
	ft_lstadd_back(&l, l2);
	ft_lstadd_back(&l, l3);
	test = ft_lstmap(l, (void *)ft_strlen, free);
	freeList(l);
	return (0);
}*/
