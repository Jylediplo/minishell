/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pantoine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 15:57:19 by pantoine          #+#    #+#             */
/*   Updated: 2023/11/14 16:15:54 by pantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	int	i;

	i = -1;
	while (++i, (s1[i] || s2[i]) && (size_t)i < n)
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
	}
	return (0);
}
/*
#include <stdio.h>
int	main(void)
{
	printf("%d", ft_strncmp("LULE", "LUL", 3));
	return (0);
}*/
