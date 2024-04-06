/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pantoine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 16:13:56 by pantoine          #+#    #+#             */
/*   Updated: 2023/11/09 16:23:35 by pantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memset(void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*p;

	p = s;
	i = 0;
	while (i < n)
		p[i++] = (unsigned char)c;
	return (s);
}
/*
#include <stdio.h>
#include <string.h>
int	main(void)
{
	int	test[5] = {0, 1, 2, 3, 4};
	int	test2[5] = {0, 1, 2, 3, 4};
	void	*ptr = test;
	void	*ptr2 = test2;

	printf("%s\n", (char *)ft_memset(ptr, 'a', 25));
	printf("%s\n", (char *)memset(ptr2, 'a', 25));
	return (0);
}*/
