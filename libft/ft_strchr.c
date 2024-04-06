/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pantoine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 14:20:28 by pantoine          #+#    #+#             */
/*   Updated: 2023/11/15 16:16:38 by pantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = -1;
	while (++i, s[i])
	{
		if (s[i] == (unsigned char)c)
			return ((char *)s + i);
	}
	if ((unsigned char)c == '\0')
		return ((char *)s + i);
	return (0);
}
/*
#include <stdio.h>
#include <string.h>
int	main(void)
{
	printf("%p\n", &(*ft_strchr("teste", 1023)));
	printf("%p\n", &(*strchr("teste", 1023)));
	return (0);
}*/
