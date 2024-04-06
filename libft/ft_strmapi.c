/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pantoine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 15:07:55 by pantoine          #+#    #+#             */
/*   Updated: 2023/11/17 15:39:03 by pantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	char			*res;

	i = 0;
	res = (char *)malloc((ft_strlen(s) + 1) * sizeof(char));
	if (!res)
		return (NULL);
	while (i < (unsigned int)ft_strlen(s))
	{
		res[i] = f(i, s[i]);
		i++;
	}
	res[i] = '\0';
	return (res);
}
/*
char addOne(unsigned int i, char c) {return (i + c);}

#include <stdio.h>
int	main(void)
{
	char	*test;

	test = ft_strmapi("1234", addOne);
	//printf("%s", test);
	free(test);
	return (0);
}*/
