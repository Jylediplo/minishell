/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pantoine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 14:23:43 by pantoine          #+#    #+#             */
/*   Updated: 2023/11/15 17:52:05 by pantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static char	*opt_malloc(char const *s, unsigned int start, size_t len)
{
	char	*res;

	res = NULL;
	if (start > ft_strlen(s))
	{
		res = malloc(sizeof(char));
		if (!res)
			return (NULL);
		res[0] = '\0';
		return (res);
	}
	else if (len > ft_strlen(s) - start)
		res = malloc((ft_strlen(s) - start + 1) * sizeof(char));
	else if (len <= ft_strlen(s) - start)
		res = malloc((len + 1) * sizeof(char));
	return (res);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*res;
	size_t	i;

	i = (size_t)start;
	res = opt_malloc(s, start, len);
	if (!res)
		return (NULL);
	while (i < len + (size_t)start && i < ft_strlen(s))
	{
		if (start > ft_strlen(s))
			break ;
		res[i - (size_t)start] = s[i];
		i++;
	}
	res[i - (size_t)start] = '\0';
	return (res);
}
/*
#include <stdio.h>
int	main(void)
{
	char	*test;
	char	*test2;

	test2 = ft_strdup("1");
	test = ft_substr(test2, 42, 42000000);
	printf("%s", test);
	free(test);
	free(test2);
	return (0);
}*/
