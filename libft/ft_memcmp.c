/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pantoine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 16:28:07 by pantoine          #+#    #+#             */
/*   Updated: 2023/11/09 17:13:15 by pantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*cs1;
	const unsigned char	*cs2;
	size_t				i;

	i = -1;
	cs1 = s1;
	cs2 = s2;
	while (++i, i < n)
	{
		if (cs1[i] != cs2[i])
			return (cs1[i] - cs2[i]);
	}
	return (0);
}
/*
#include <stdio.h>
#include <string.h>
int	main(void)
{
	printf("%d", ft_memcmp("abcDEF", "abcdef", 4));
	printf("%d", memcmp("abcDEF", "abcdef", 4));
	return (0);
}*/
