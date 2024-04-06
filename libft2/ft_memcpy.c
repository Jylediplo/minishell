/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pantoine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 09:42:23 by pantoine          #+#    #+#             */
/*   Updated: 2023/11/15 09:15:41 by pantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	const unsigned char	*temp;
	unsigned char		*dest2;

	if (!src && !dest)
		return (dest);
	temp = src;
	dest2 = dest;
	while (n)
	{
		*(dest2) = *(temp);
		dest2++;
		temp++;
		--n;
	}
	return (dest);
}
/*
#include <stdio.h>
#include <string.h>
int	main(void)
{
	char	test[8] = "abcdefg";
	void	*test1;
	char	test2[8] = "abcdefg";
	void	*test3;

	test1 = test;
	test3 = test2;
	printf("%s\n", (char *)ft_memcpy(((void *)0), ((void *)0), 4));
	//printf("%s", (char *)memcpy((void *)0, (void *)0, 4));
	return (0);
}*/
