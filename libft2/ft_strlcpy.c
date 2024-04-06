/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pantoine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 18:50:32 by pantoine          #+#    #+#             */
/*   Updated: 2023/11/14 13:32:24 by pantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	len_src;

	len_src = ft_strlen(src);
	if (len_src + 1 < size)
		ft_memcpy(dest, src, len_src + 1);
	else if (size != 0)
	{
		ft_memcpy(dest, src, size - 1);
		dest[size - 1] = '\0';
	}
	return (len_src);
}
/*
#include <bsd/string.h>
#include <stdio.h>
int	main(void)
{
	char	buff1[4];
	char	buff2[4];
	
	printf("%zd\n", ft_strlcpy(buff2, "yayyy", 5));
	printf("%zd", strlcpy(buff1, "yayyy", 5));
	return (0);
}*/
