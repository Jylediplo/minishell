/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pantoine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 16:49:15 by pantoine          #+#    #+#             */
/*   Updated: 2023/11/11 16:44:59 by pantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*res;
	int		i;

	i = -1;
	res = malloc((ft_strlen(s) + 1) * sizeof(char));
	if (!res)
		return (NULL);
	while (++i, s[i])
		res[i] = s[i];
	res[i] = '\0';
	return (res);
}
/*
#include <stdio.h>
#include <string.h>
int	main(void)
{
	char	*test;

	test = ft_strdup("0123456789");
	printf("%s", test);
	free(test);
	return (0);
}*/
