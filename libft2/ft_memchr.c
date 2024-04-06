/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pantoine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 18:18:59 by pantoine          #+#    #+#             */
/*   Updated: 2023/11/09 09:41:55 by pantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t				i;
	const unsigned char	*p;

	p = s;
	i = 0;
	while (i < n)
	{
		if (p[i] == (unsigned char)c)
			return ((void *)s + i);
		i++;
	}
	return (0);
}
/*
#include <stdio.h>
#include <string.h>
int	main(void)
{
	const char	*test = "ooooolpp";
	const void	*test2;
	const char	*test3 = "ooooolpp";
	const void	*test4;

	test2 = test;
	test4 = test3;
	printf("%s", (char *)ft_memchr(test2, 'l', 5));
	printf("%s", (char *)memchr(test4, 'l', 5));
	return (0);
}*/
