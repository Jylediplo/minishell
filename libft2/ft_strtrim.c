/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pantoine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 17:43:48 by pantoine          #+#    #+#             */
/*   Updated: 2023/11/11 19:11:27 by pantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static int	isinset(char const c, char const *set)
{
	int	i;

	i = -1;
	while (++i, set[i])
	{
		if (c == set[i])
			return (1);
	}
	return (0);
}

static int	get_size(char const *s1, char const *set)
{
	int	res;
	int	i;

	i = 0;
	res = 0;
	while (s1[i] && isinset(s1[i], set))
	{
		i++;
		res++;
	}
	if (!s1[i])
		return (0);
	i = ft_strlen(s1) - 1;
	while (isinset(s1[i], set))
	{
		i--;
		res++;
	}
	return ((int)ft_strlen(s1) - res);
}

static char	*copystring(char const *src, char *dst, char const *set)
{
	int	i;
	int	j;

	i = 0;
	j = -1;
	while (src[i] && isinset(src[i], set))
		i++;
	while (++j, src[i] && j < get_size(src, set))
	{
		dst[j] = src[i];
		i++;
	}
	dst[j] = '\0';
	return (dst);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*res;

	res = (char *)malloc((get_size(s1, set) + 1) * sizeof(char));
	if (!res)
		return (NULL);
	return (copystring(s1, res, set));
}
/*
int	main(void)
{
	char	*test;

	test = ft_strtrim("   xxx   xxx", " x");
	printf("%s", test);
	free(test);
	return (0);
}*/
