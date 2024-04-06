/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pantoine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 16:14:51 by pantoine          #+#    #+#             */
/*   Updated: 2023/11/12 17:41:05 by pantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	int	i;

	i = -1;
	while (++i, s[i])
		f(i, &s[i]);
}
/*
void	iter(unsigned int i, char *s)
{
	*s += i;
}

#include <stdio.h>
int	main(void)
{
	char	test[11] = "0000000000";

	ft_striteri(test, iter);
	printf("%s", test);
	return (0);
}*/
