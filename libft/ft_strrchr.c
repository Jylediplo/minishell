/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pantoine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 14:47:11 by pantoine          #+#    #+#             */
/*   Updated: 2023/11/15 16:16:27 by pantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strrchr(const char *s, int c)
{
	int	i;
	int	p;

	i = -1;
	p = -1;
	while (++i, s[i])
	{
		if (s[i] == (unsigned char)c)
			p = i;
	}
	if ((unsigned char)c == '\0')
		return ((char *)s + i);
	if (p == -1)
		return (0);
	return ((char *)s + p);
}
/*
#include <stdio.h>
#include <string.h>
int	main(void)
{
	printf("%p\n", &(*ft_strrchr("tripouille", '\0')));
	printf("%p\n", &(*strrchr("tripouille", '\0')));
	return (0);
}*/
