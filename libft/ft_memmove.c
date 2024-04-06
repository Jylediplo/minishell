/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pantoine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 10:22:25 by pantoine          #+#    #+#             */
/*   Updated: 2023/11/15 17:48:35 by pantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdint.h>
#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t		i;
	char		*cdest;
	const char	*csrc;

	i = n;
	if (!src && !dest)
		return (NULL);
	cdest = dest;
	csrc = src;
	if (dest < src)
		return (ft_memcpy(dest, src, n));
	else
	{
		while (i > 0)
		{
			cdest[i - 1] = csrc[i - 1];
			i--;
		}
	}
	return (dest);
}
/*
#include <string.h>
int	main(void)
{
	char	testsrc[7] = "bonjour";
	char	*first;
	char	*second;

	first = testsrc;
	second = testsrc;
	printf("%s\n", (char *)ft_memmove(second + 3, first, 4));
	//printf("%s", (char *)memmove(second + 3, first, 3));
	return (0);
}*/
