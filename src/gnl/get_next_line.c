/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pantoine <pantoine@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 19:57:58 by pantoine          #+#    #+#             */
/*   Updated: 2024/05/09 12:10:25 by pantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/get_next_line.h"

char	*mres(t_list_gnl **head, int fd, ssize_t fp)
{
	size_t		i;
	size_t		j;
	t_list_gnl	*temp;

	temp = *head;
	j = 0;
	while (temp)
	{
		i = 0;
		while ((temp->content)[i] && fd == temp->fd)
		{
			if ((temp->content)[i++] == '\n')
				return ((char *)malloc(sizeof(char) * (j + 2)));
			j++;
		}
		if (!(temp->content[i]) && fp == 0 && !(temp->next))
			return ((char *)malloc(sizeof(char) * j + 1));
		temp = temp->next;
	}
	return (NULL);
}

char	*cleanstring(t_list_gnl **head, char *res, ssize_t j, ssize_t i)
{
	ssize_t	sz;
	char	*temp;

	sz = 0;
	if (((*head)->content)[i])
	{
		while (((*head)->content)[sz + i])
			sz++;
		temp = malloc(sizeof(char) * (sz + 1));
		if (!temp)
			return (NULL);
		sz = -1;
		while (++sz, (*head)->content[sz + i])
			temp[sz] = (*head)->content[sz + i];
		temp[sz] = '\0';
		free((*head)->content);
		(*head)->content = temp;
	}
	else
		*head = lstclear(head, *head, 0);
	res[j + 1] = '\0';
	return (res);
}

void	move_tofront(t_list_gnl **head, int fd)
{
	t_list_gnl	*current;
	t_list_gnl	*previous;

	current = *head;
	previous = NULL;
	if ((*head)->next == NULL)
		return ;
	while (current && current->fd != fd)
	{
		previous = current;
		current = current->next;
	}
	if (!current)
		return ;
	previous->next = current->next;
	current->next = *head;
	*head = current;
}

char	*return_line(t_list_gnl	**head, int fd, ssize_t fp)
{
	char		*res;
	ssize_t		i;
	ssize_t		j;

	j = 0;
	res = mres(head, fd, fp);
	if (!res)
		return (NULL);
	while (*head)
	{
		i = 0;
		if ((*head)->content[i] && fd != (*head)->fd)
			move_tofront(head, fd);
		while (((*head)->content)[i] && fd == (*head)->fd)
		{
			res[j] = ((*head)->content)[i++];
			if (res[j] == '\n' || (fp == 0 && !((*head)->content[i])
					&& !(fd_in_list(*head, fd))))
				return (cleanstring(head, res, j, i));
			j++;
		}
		*head = lstclear(head, *head, 0);
	}
	return (NULL);
}

char	*get_next_line(int fd)
{
	void				*buff;
	char				*res;
	ssize_t				fp;
	static t_list_gnl	*mem = NULL;

	if (BUFFER_SIZE <= 0 || fd < 0 || read(fd, 0, 0) < 0)
		return (NULL);
	buff = malloc(BUFFER_SIZE);
	if (!buff)
		return (NULL);
	fp = read(fd, buff, BUFFER_SIZE);
	if (fp == -1 || (fp == 0 && mem == NULL))
	{
		free(buff);
		return (NULL);
	}
	else if (fp != 0)
		read_buff(buff, &mem, fd, &fp);
	free(buff);
	if (!mem)
		return (NULL);
	res = return_line(&mem, fd, fp);
	if (!res)
		lstclear(&mem, NULL, 1);
	return (res);
}
