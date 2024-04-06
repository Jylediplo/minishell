/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pantoine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 14:59:06 by pantoine          #+#    #+#             */
/*   Updated: 2023/11/10 16:13:56 by pantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	const char	*csrc;
	char		*cdst;
	size_t		i;
	size_t		len_dst;

	cdst = dst;
	csrc = src;
	i = size;
	while (*cdst && i-- != 0)
		cdst++;
	len_dst = cdst - dst;
	i = size - len_dst;
	if (i == 0)
		return (len_dst + ft_strlen(csrc));
	while (*csrc)
	{
		if (i != 1)
		{
			*cdst++ = *csrc;
			i--;
		}
		csrc++;
	}
	*cdst = '\0';
	return (len_dst + (csrc - src));
}
/*
#include <stdio.h>
#include <bsd/string.h>
int	main(void)
{
	char	dst[30] = "ok";
	char	dst2[30] = "ok";
	printf("%zd\n", ft_strlcat(dst, "", 5));
	printf("%zd", strlcat(dst2, "", 5));
	return (0);
}*/
