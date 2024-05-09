/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pantoine <pantoine@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 19:58:18 by pantoine          #+#    #+#             */
/*   Updated: 2024/05/09 12:14:17 by pantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

typedef struct s_list_gnl {
	char				*content;
	int					fd;
	struct s_list_gnl	*next;
}	t_list_gnl;
char	*get_next_line(int fd);
char	*return_line(t_list_gnl	**head, int fd, ssize_t fp);
void	move_tofront(t_list_gnl **head, int fd);
char	*mres(t_list_gnl **head, int fd, ssize_t fp);
char	*cleanstring(t_list_gnl **head, char *res, ssize_t j, ssize_t i);
t_list_gnl	*read_buff(char *buff, t_list_gnl **mem, int fd, ssize_t *fp);
t_list_gnl	*new_mem(t_list_gnl **head, char *buff, ssize_t end, int fd);
void	addback(t_list_gnl **lst, t_list_gnl *new);
t_list_gnl	*lstclear(t_list_gnl **head, t_list_gnl *lst, int typeclear);
int		fd_in_list(t_list_gnl *current, int fd);

#endif
