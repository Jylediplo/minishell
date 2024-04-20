/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pantoine <pantoine@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 12:42:38 by pantoine          #+#    #+#             */
/*   Updated: 2023/12/07 18:28:37 by pantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	fd_in_list(t_list *current, int fd)
{
	t_list	*temp;

	temp = current->next;
	while (temp)
	{
		if (temp->fd == fd)
			return (1);
		temp = temp->next;
	}
	return (0);
}

t_list	*lstclear(t_list **head, t_list *lst, int typeclear)
{
	t_list	*nextn;

	if (typeclear == 1)
	{
		while (*head)
		{
			nextn = (*head)->next;
			free((*head)->content);
			free(*head);
			*head = nextn;
		}
		*head = NULL;
		return (NULL);
	}
	if (!lst)
		return (NULL);
	nextn = lst->next;
	free(lst->content);
	free(lst);
	return (nextn);
}

void	addback(t_list **lst, t_list *new)
{
	t_list	*last;

	if (!(*lst))
	{
		*lst = new;
		return ;
	}
	last = *lst;
	while (last->next != NULL)
		last = last->next;
	last->next = new;
}

t_list	*new_mem(t_list **head, char *buff, ssize_t end, int fd)
{
	t_list	*res;
	ssize_t	i;

	i = 0;
	res = (t_list *)malloc(sizeof(t_list));
	if (!res)
		return (NULL);
	res->content = (char *)malloc(sizeof(char) * (end + 1));
	if (!(res->content))
	{
		free(res);
		return (NULL);
	}
	res->fd = fd;
	while (i < end)
	{
		(res->content)[i] = buff[i];
		i++;
	}
	(res->content)[i] = '\0';
	res->next = NULL;
	addback(head, res);
	return (res);
}

t_list	*read_buff(char *buff, t_list **mem, int fd, ssize_t *fp)
{
	ssize_t		i;

	i = -1;
	while (++i, buff[i] != '\n' && *fp)
	{
		if (i == *fp - 1)
		{
			if (!new_mem(mem, buff, i + 1, fd))
				return (lstclear(mem, NULL, 1));
			*fp = read(fd, buff, BUFFER_SIZE);
			if (*fp == -1)
				return (lstclear(mem, NULL, 1));
			i = -1;
		}
	}
	if (!(*fp))
		return (NULL);
	if (!new_mem(mem, buff, i + 1, fd))
		return (lstclear(mem, NULL, 1));
	if (i < *fp - 1)
	{
		if (!new_mem(mem, buff + i + 1, *fp - i - 1, fd))
			return (lstclear(mem, NULL, 1));
	}
	return (NULL);
}
