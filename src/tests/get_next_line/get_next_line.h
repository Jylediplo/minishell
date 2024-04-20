/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pantoine <pantoine@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 19:58:18 by pantoine          #+#    #+#             */
/*   Updated: 2024/04/20 15:02:45 by pantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H
# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

typedef struct s_list {
	char			*content;
	int				fd;
	struct s_list	*next;
}	t_list;
char	*get_next_line(int fd);
char	*return_line(t_list	**head, int fd, ssize_t fp);
void	move_tofront(t_list **head, int fd);
char	*mres(t_list **head, int fd, ssize_t fp);
char	*cleanstring(t_list **head, char *res, ssize_t j, ssize_t i);
t_list	*read_buff(char *buff, t_list **mem, int fd, ssize_t *fp);
t_list	*new_mem(t_list **head, char *buff, ssize_t end, int fd);
void	addback(t_list **lst, t_list *new);
t_list	*lstclear(t_list **head, t_list *lst, int typeclear);
int		fd_in_list(t_list *current, int fd);

#endif
