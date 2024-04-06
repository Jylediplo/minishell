/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pantoine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 17:28:30 by pantoine          #+#    #+#             */
/*   Updated: 2023/11/11 19:12:24 by pantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*res;
	int		i;
	int		lens1;

	i = -1;
	lens1 = ft_strlen(s1);
	res = (char *)malloc((lens1 + ft_strlen(s2) + 1) * sizeof(char));
	if (!res)
		return (NULL);
	while (++i, s1[i])
		res[i] = s1[i];
	while (s2[i - lens1])
	{
		res[i] = s2[i - lens1];
		i++;
	}
	res[i] = '\0';
	return (res);
}
/*
#include <stdio.h>
int	main(void)
{
	char	*test;
	
	test = ft_strjoin("AAA", "");
	printf("%s", test);
	free(test);
	return (0);
}*/
