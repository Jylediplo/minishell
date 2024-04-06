/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pantoine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 17:36:19 by pantoine          #+#    #+#             */
/*   Updated: 2023/11/11 11:22:41 by pantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!(little[0]))
		return ((char *)big);
	while (big[i] && i < len)
	{
		while (little[j] && i + j < len)
		{
			if (big[i + j] != little[j])
				break ;
			j++;
		}
		if (!(little[j]))
			return ((char *)big + i);
		j = 0;
		i++;
	}
	return (0);
}
/*
#include <stdio.h>
#include <bsd/string.h>
int	main(void)
{
	printf("%s\n", ft_strnstr("aaabcabcd", "cd", 8));
	printf("%s", strnstr("", "", 10));
	return (0);
}*/
